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

void Airfoil::construct
(
	const input::Radius& radius,
	const input::DeviationAngle& delta
)
{
	// general
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
		data_->cref<input::RootOutletVelocity>(),
		data_->cref<input::VortexDistributionExponent>(),
		radius,
		data_->cref<input::HubRadius>()
	};
	input::StaticPressureDifference dp
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
		delta
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
	input::TurbulenceReferenceLengthScale L_turb
	{
		chord,
		data_->cref<input::TurbulenceReferenceLengthScaleRatio>()
	};
	input::TurbulenceDissipationRate epsilon
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L_turb
	};
	input::TurbulenceSpecificDissipationRate omega
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L_turb
	};
	input::TurbulenceViscosity nut
	{
		data_->cref<input::TurbulenceKineticEnergy>(),
		L_turb
	};

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(chord),
		delta,
		std::move(dp),
		std::move(epsilon),
		std::move(L_turb),
		std::move(nut),
		std::move(omega),
		std::move(pitch),
		radius,
		std::move(U),
		std::move(w_1)
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const input::Radius& radius,
	const input::DeviationAngle& delta,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"airfoil.step", parentCwd, id}
{
	construct(radius, delta);
}


Airfoil::Airfoil
(
	const input::Radius& radius,
	const input::Registry& reg,
	const input::DeviationAngle& delta,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"airfoil.step", reg, parentCwd, id}
{
	construct(radius, delta);
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
	// compute and store monitoring plane positions and
	// periodic patch translation vectors
	input::storeAll
	(
		*data_,
		input::LEMonitoringPlane
		{
			profile.lePoint(),
			data_->cref<input::Chord>(),
			data_->cref<input::MonitoringPlaneOffset>()
		},
		input::TEMonitoringPlane
		{
			profile.lePoint(),
			data_->cref<input::Chord>(),
			data_->cref<input::MonitoringPlaneOffset>()
		},
		input::TranslationPerBot
		{
			data_->cref<input::Pitch>()
		},
		input::TranslationPerTop
		{
			data_->cref<input::Pitch>()
		}
	);

	simulation::Simulator sim {*data_, simId_, cwd_};

	// make the mesh if we're running just the single sim
	if (!mesh)
		mesh.reset
		(
			new mesh::ProfileMesh {*data_, model_, sim.caseDirectory}
		);
	// change the mesh working directory if we're designing
	else
		mesh->setCwd(sim.caseDirectory);

	mesh->build(profile);
	mesh->write();

	sim.simulate();

	++simId_;

	return sim.caseDirectory;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
