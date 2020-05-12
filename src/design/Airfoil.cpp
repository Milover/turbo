/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "Airfoil.h"

#include "Error.h"
#include "General.h"
#include "GmshWrite.h"
#include "InputRegistry.h"
#include "Model.h"
#include "Profile.h"
#include "ProfileGenerator.h"
#include "ProfileMesh.h"
#include "Registry.h"
#include "Simulator.h"
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
	// general
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
	input::InletRelativeVelocity w_1
	{
		data_->cref<input::InletVelocity>(),
		U
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
		data_->cref<input::IncidenceAngle>(),
		data_->cref<input::DeviationAngle>()
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

	// turbulence
	input::TurbulenceReferenceLengthScale L
	{
		chord,
		data_->cref<input::TurbulenceReferenceLengthScaleRatio>()
	};
	input::TurbulenceDissipationRate epsilon
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L
	};
	input::TurbulenceSpecificDissipationRate omega
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L
	};
	input::TurbulenceViscosity nut
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L
	};

	// periodic patch translations
	input::TranslationPerBot trBot {pitch};
	input::TranslationPerTop trTop {pitch};

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(chord),
		std::move(dp),
		std::move(epsilon),
		std::move(L),
		std::move(nut),
		std::move(omega),
		std::move(pitch),
		std::move(radius),
		std::move(trBot),
		std::move(trTop),
		std::move(U),
		std::move(w_1)
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
	stationNo_ {stationNo}
{
	setFile("airfoil", ".step");

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
	stationNo_ {stationNo}
{
	setFile("airfoil", ".step");

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
	profile.build(generator, *data_);
}


Path Airfoil::simulate(Sptr<mesh::ProfileMesh> mesh)
{
	Path caseDir
	{
		simulation::Simulator::createCase(file_.parent_path())
	};

	// make the mesh if we're running just the single sim
	if (!mesh)
		mesh.reset
		(
			new mesh::ProfileMesh {*data_, model_, caseDir}
		);
	// change the mesh output directory if we're designing
	else
		mesh->changeDirectory(caseDir);

	mesh->build(profile);
	mesh->write();

	Uptr<simulation::Simulator> sim
	(
		new simulation::Simulator
		{
			*data_,
			caseDir,
			mesh->file()
		}
	);
	sim->simulate();

	return caseDir;
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
