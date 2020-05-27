/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <vector>

#include "Blade.h"

#include "Airfoil.h"
#include "FilledSurface.h"
#include "General.h"
#include "InputRegistry.h"
#include "Loft.h"
#include "Registry.h"
#include "SkewDistribution.h"
#include "Spline.h"
#include "Surface.h"
#include "TurboBase.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Blade::construct()
{
	input::KinematicViscosity nu
	{
		data_->cref<input::Density>(),
		data_->cref<input::DynamicViscosity>()
	};
	input::InletVelocity c_1
	{
		data_->cref<input::VolumeFlowRate>(),
		data_->cref<input::HubRadius>(),
		data_->cref<input::ShroudRadius>()
	};
	input::RootOutletVelocity c_2_h
	{
		c_1,
		data_->cref<input::StaticPressureDifference>(),
		data_->cref<input::Rps>(),
		data_->cref<input::HubRadius>(),
		data_->cref<input::Density>()
	};
	input::TurbulenceKineticEnergy k
	{
		c_1,
		data_->cref<input::TurbulenceIntensity>()
	};
	input::storeAll
	(
		*data_,
		std::move(c_1),
		std::move(c_2_h),
		std::move(k),
		std::move(nu)
	);
	// we allow this to be user defined
	if
	(
		!input::InputRegistry::has(input::VortexDistributionExponent::name)
	)
		data_->store
		(
			input::VortexDistributionExponent
			{
				c_2_h,
				data_->cref<input::StaticPressureDifference>(),
				data_->cref<input::Rps>(),
				data_->cref<input::HubRadius>(),
				data_->cref<input::ShroudRadius>(),
				data_->cref<input::Density>()
			}
		);

	// build airfoils
	std::size_t numStations
	{
		static_cast<std::size_t>(data_->cref<input::NumberOfStations>().value())
	};
	airfoils_.reserve(numStations);
	for (std::size_t station {0}; station < numStations; ++station)
	{
		input::Radius radius
		{
			static_cast<Integer>(station),
			data_->cref<input::NumberOfStations>(),
			data_->cref<input::HubRadius>(),
			data_->cref<input::ShroudRadius>(),
			data_->cref<input::TipClearance>()
		};

		airfoils_.emplace_back
		(
			new Airfoil
			{
				radius,
				*data_,
				input::DeviationAngle {},
				cwd_,
				station
			}
		);
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Blade::Blade
(
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"blade.step", parentCwd, id}
{
	construct();
}


Blade::Blade
(
	const input::Registry& reg,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"blade.step", reg, parentCwd, id}
{
	construct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const Uptrvector<Airfoil>& Blade::airfoilsCRef() const
{
	return airfoils_;
}


Uptrvector<Airfoil>& Blade::airfoilsRef()
{
	return airfoils_;
}


// FIXME:
// 		Reimplement:
// 			implement a math-spline class (B-spline, NURBS, Catmul-Rom...)
// 			and use instead of geometric splines to generate the interpolated
// 			profiles, then loft the contours.
// 		Implement:
// 			we have to handle cases when airfoils_.size() == 1
void Blade::build()
{
	model_->activate();

	// create hub/shroud airfoils if airfoils_.size() == 1

	// get profiles
	std::vector<Profile> profiles;
	profiles.reserve(airfoils_.size());

	for (auto& a : airfoils_)
		profiles.emplace_back(a->profile);

	// wrap and apply skew
	SkewDistribution sd {*data_};
	for (auto& p : profiles)
	{
		sd.skew(p);
		p.wrap();
	}

	// make main surface splines
	Sptrvector<geometry::Curve> topSplines;				// suction
	Sptrvector<geometry::Curve> botSplines;				// pressure
	topSplines.reserve(profiles.front().size());
	botSplines.reserve(profiles.front().size());

	// for each profile point-pair [top, bot]
	std::vector<Profile::Point> tmpTop;
	std::vector<Profile::Point> tmpBot;
	tmpTop.reserve(profiles.size());
	tmpBot.reserve(profiles.size());

	for (std::size_t i {0}; i < profiles.front().size(); ++i)
	{
		tmpTop.clear();
		tmpBot.clear();

		for (auto& p : profiles)
		{
			tmpTop.emplace_back(p[i].first);
			tmpBot.emplace_back(p[i].second);
		}

		topSplines.emplace_back
		(
			new geometry::Spline {tmpTop}
		);
		botSplines.emplace_back
		(
			new geometry::Spline {tmpBot}
		);
	}

	// make surfaces
	Sptr<geometry::Surface> topSurf
	{
		new geometry::Surface
		{
			geometry::operators::Loft {}(topSplines)
		}
	};
	// the joining spline has to be toplogically identical
	botSplines.front() = topSurf->boundaryCRef()[0];
	Sptr<geometry::Surface> botSurf
	{
		new geometry::Surface
		{
			geometry::operators::Loft {}(botSplines)
		}
	};
	Sptr<geometry::Surface> teSurf
	{
		new geometry::Surface
		{
			geometry::operators::Loft {}
			(
				topSurf->boundaryCRef()[2],
				botSurf->boundaryCRef()[2]
			)
		}
	};

	geometry_.reset
	(
		new geometry::Volume
		{
			topSurf,
			botSurf,
			teSurf,
			geometry::FilledSurface						// lower surface
			{
				topSurf->boundaryCRef()[1],
				botSurf->boundaryCRef()[1],
				teSurf->boundaryCRef()[1]
			},
			geometry::FilledSurface						// upper surface
			{
				topSurf->boundaryCRef()[3],
				botSurf->boundaryCRef()[3],
				teSurf->boundaryCRef()[3]
			}
		}
	);

}


Sptr<geometry::Volume> Blade::geometry() const noexcept
{
	return geometry_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
