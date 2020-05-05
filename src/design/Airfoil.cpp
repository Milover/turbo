/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "Airfoil.h"

#include "Geometry.h"
#include "Profile.h"
#include "ProfileGenerator.h"
#include "TurboBase.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Airfoil::construct()
{
	// compute
	input::BladeVelocity U
	{
		data_->cref<input::Rps>(),
		data_->cref<input::Radius>()
	};
	input::OutletVelocity c_2
	{
		data_->cref<input::InletVelocity>(),
		data_->cref<input::RootOutletVelocity>(),
		data_->cref<input::VortexDistributionExponent>(),
		data_->cref<input::Radius>(),
		data_->cref<input::HubRadius>(),
		U
	};
	input::TotalPressureDifference dp
	{
		data_->cref<input::InletVelocity>(),
		c_2,
		U,
		data_->cref<input::Density>()
	};
	input::CamberAngle camber
	{
		data_->cref<input::InletVelocity>(),
		c_2,
		U,
		data_->cref<input::IncidenceAngle>()
	};
	input::Pitch pitch
	{
		data_->cref<input::NumberOfBlades>(),
		data_->cref<input::Radius>()
	};
	input::Chord chord
	{
		pitch,
		data_->cref<input::Solidity>()
	};

	// because we need the basic geometry
	// to compute the stagger
	ProfileGenerator generator {camber};

	input::StaggerAngle stagger
	{
		data_->cref<input::InletVelocity>(),
		U,
		input::InclinationAngle
		{
			generator.inclination(0.0)		// leading edge inclination
		},
		data_->cref<input::IncidenceAngle>()
	};

	// now we can build it properly
	profile.build
	(
		generator,
		chord,
		data_->cref<input::Radius>(),
		stagger
	);

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(chord),
		std::move(dp),
		std::move(pitch),
		std::move(stagger),
		std::move(U)
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil(const input::Radius& r)
{
	data_->store(input::Radius {r});

	construct();
}


Airfoil::Airfoil
(
	const input::Radius& r,
	const input::Registry& reg
)
:
	TurboBase {reg}
{
	data_->store(input::Radius {r});

	construct();
}


Airfoil::Airfoil
(
	const input::Radius& r,
	const input::Registry& reg,
	geometry::Model&& mod
)
:
	TurboBase
	{
		reg,
		std::move(mod)
	}
{
	data_->store(input::Radius {r});

	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
