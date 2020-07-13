/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <filesystem>
#include <sstream>
#include <utility>
#include <vector>

#include "Blade.h"

#include "Airfoil.h"
#include "CsvWriter.h"
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
	input::TurbulenceKineticEnergy k
	{
		c_1,
		data_->cref<input::TurbulenceIntensity>()
	};
	input::SolidityDistribution solidityDistr
	{
		data_->cref<input::SolidityDistribution>()
	};
	input::storeAll
	(
		*data_,
		std::move(c_1),
		std::move(k),
		std::move(nu),
		std::move(solidityDistr)
	);

	// we allow these to be user input
	if
	(
		!data_->storeFromInput<input::RootOutletVelocity>()
	)
		data_->store
		(
			input::RootOutletVelocity
			{
				c_1,
				data_->cref<input::BladeEfficiency>(),
				data_->cref<input::Rps>(),
				data_->cref<input::HubRadius>()
			}
		);
	if
	(
		!data_->storeFromInput<input::VortexDistributionExponent>()
	)
		data_->store
		(
			input::VortexDistributionExponent
			{
				data_->cref<input::RootOutletVelocity>(),
				data_->cref<input::TargetStaticPressureDifference>(),
				data_->cref<input::BladeEfficiency>(),
				data_->cref<input::Rps>(),
				data_->cref<input::HubRadius>(),
				data_->cref<input::ShroudRadius>(),
				data_->cref<input::Density>()
			}
		);

	// these are optional
	data_->storeFromInput<input::MaxAbsBladeThicknessDistribution>();
	data_->storeFromInput<input::MaxPassageWidthDistribution>();

	// build airfoils
	std::size_t numStations
	{
		static_cast<std::size_t>(data_->cref<input::NumberOfStations>().value())
	};
	airfoils_.reserve(numStations);
	for (auto station {0ul}; station < numStations; ++station)
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
// 		Issue:
// 			using splines to interpolate intermediate profiles causes issues
// 			wherein the requested passage width is not satisfied because
// 			the spline bends outward on parts of the span with uniform
// 			passage width. In general there seem to be transition issues
// 			when enough stations are requested and the blade is of uniform
// 			width, so we should think about how this cam be fixed.
void Blade::build()
{
	model_->activate();

	auto profiles {prepProfiles()};

// FIXME: should be added at some point
//std::filesystem::create_directory(cwd_ / "profiles");
//auto count {0};
//for (auto& p : profiles)
//{
//	String name {"profile."};
//	name += std::to_string(count);
//
//	Path tmp {cwd_ / "profiles" / name.c_str()};
//
//	p.writeCsv(tmp);
//
//	++count;
//}

// FIXME: we should add this at some point
//for (auto& p : profiles)
//{
//	new geometry::Spline {p.getContour()};
//}

	if (profiles.empty())
		return;

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

//	write();
//	std::exit(0);
}


Sptr<geometry::Surface> Blade::midPlane() const
{
	auto profiles {prepProfiles()};

	if (profiles.empty())
		return nullptr;

	std::vector<std::vector<Profile::Point>> points;
	points.reserve(profiles.size());

	for (const auto& p : profiles)
		points.emplace_back(p.camberLinePoints());

	Sptrvector<geometry::Curve> curves;
	std::vector<Profile::Point> tmp;

	curves.reserve(profiles.size());
	tmp.reserve(profiles.front().size());

	for (auto i {0ul}; i < profiles.front().size(); ++i)
	{
		tmp.clear();
		for (const auto& camberline : points)
			tmp.emplace_back(camberline[i]);

		curves.emplace_back
		(
			new geometry::Spline {tmp}
		);
	}

	return Sptr<geometry::Surface>
	{
		new geometry::Surface
		{
			geometry::operators::Loft {}(std::move(curves))
		}
	};
}


Sptr<geometry::Volume> Blade::geometry() const noexcept
{
	return geometry_;
}


std::vector<Profile> Blade::prepProfiles() const
{
	// handle case when airfoils_.size() == 1

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

	return profiles;
}


void Blade::writeStationData(const Path& file) const
{
	bool designed {true};
	for (auto& a : airfoils_)
		designed = designed
				&& a->designed();

	CsvWriter bladeCsv {file};
	if (designed)
		bladeCsv.writeHeader
		(
			"id",
			"target tot. pressure",
			"tot. pressure",
			"eta",
			"pressure",
			"swirl_2",
			"f_x",
			"f_y",
			"radius",
			"chord",
			"beta_1'",
			"beta_2'",
			"camber",
			"stagger"
		);
	else
		bladeCsv.writeHeader
		(
			"id",
			"radius",
			"chord",
			"beta_1'",
			"beta_2'",
			"camber",
			"stagger"
		);

	for (auto& a : airfoils_)
	{
		const auto& p {a->profile};

		if (designed)
			bladeCsv.write
			(
				a->id(),
				a->cref<input::TargetTotalPressureDifference>().value(),
				a->cref<input::TotalPressureDifference>().value(),
				a->cref<input::AirfoilEfficiency>().value(),
				a->cref<input::StaticPressureDifference>().value(),
				a->cref<input::OutletVelocity>().value().y(),
				a->cref<input::AirfoilTotalForce>().value().x(),
				a->cref<input::AirfoilTotalForce>().value().y(),
				p.radius(),
				p.chord(),
				p.inletAngle(),
				p.outletAngle(),
				p.camberAngle(),
				p.staggerAngle()
			);
		else
			bladeCsv.write
			(
				a->id(),
				p.radius(),
				p.chord(),
				p.inletAngle(),
				p.outletAngle(),
				p.camberAngle(),
				p.staggerAngle()
			);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
