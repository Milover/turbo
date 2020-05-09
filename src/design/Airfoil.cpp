/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "Airfoil.h"

#include "General.h"
#include "GmshWrite.h"
#include "Model.h"
#include "Profile.h"
#include "ProfileGenerator.h"
#include "Registry.h"
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
	input::Radius radius
	{
		stationNo_,
		data_->cref<input::NumberOfStations>(),
		data_->cref<input::HubRadius>(),
		data_->cref<input::ShroudRadius>(),
		data_->cref<input::TipClearance>()
	};
	input::BladeVelocity U
	{
		data_->cref<input::Rps>(),
		radius
	};
	input::OutletVelocity c_2
	{
		data_->cref<input::InletVelocity>(),
		data_->cref<input::RootOutletVelocity>(),
		data_->cref<input::VortexDistributionExponent>(),
		radius,
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
		radius
	};
	input::Chord chord
	{
		pitch,
		data_->cref<input::Solidity>()
	};

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(chord),
		std::move(dp),
		std::move(pitch),
		std::move(radius),
		std::move(U)
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const Integer stationNo,
	const Path& file
)
:
	TurboBase {file},
	stationNo_ {stationNo},
	profile {new Profile {}}
{
	adjustFilename("airfoil", ".step");

	construct();
}


Airfoil::Airfoil
(
	const Integer stationNo,
	const input::Registry& reg,
	const Path& file
)
:
	TurboBase {reg, file},
	stationNo_ {stationNo},
	profile {new Profile {}}
{
	adjustFilename("airfoil", ".step");

	construct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Airfoil::build()
{
	// we need the basic geometry to compute the stagger
	ProfileGenerator generator {*data_};

	data_->store
	(
		input::StaggerAngle
		{
			data_->cref<input::InletVelocity>(),
			data_->cref<input::BladeVelocity>(),
			input::InclinationAngle
			{
				generator.inclination(0.0)		// leading edge inclination
			},
			data_->cref<input::IncidenceAngle>()
		}
	);

	// now we can build it properly
	profile->build(generator, *data_);
}


void Airfoil::write() const		//	FIXME: placeholder implementation
{
	model_->activate();

	interface::GmshWrite {}(file_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
