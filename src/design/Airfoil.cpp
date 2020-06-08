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
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Airfoil::construct
(
	const input::Radius& radius,
	const input::DeviationAngle& delta
)
{
	input::RelRadius r_rel
	{
		radius,
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
	input::KinematicPressureDifference dp_kin
	{
		dp,
		data_->cref<input::Density>()
	};

	// geometry
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
	// these might change after building
	input::Solidity solidity
	{
		data_->cref<input::SolidityDistribution>().valueAt(r_rel)
	};
	input::Chord chord
	{
		pitch,
		solidity
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
		std::move(dp_kin),
		std::move(pitch),
		radius,
		std::move(r_rel),
		std::move(solidity),
		std::move(U),
		std::move(w_1)
	);

	// optional
	if (data_->has<input::MaxAbsBladeThicknessDistribution>())
		data_->store
		(
			input::MaxAbsBladeThickness
			{
				data_->
				cref<input::MaxAbsBladeThicknessDistribution>().valueAt(r_rel)
			}
		);
	if (data_->has<input::MaxPassageWidthDistribution>())
		data_->store
		(
			input::MaxPassageWidth
			{
				data_->cref<input::MaxPassageWidthDistribution>().valueAt(r_rel)
			}
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

	// now we can build the profile
	profile.build(generator, *data_);

	// compute the turbulence values
	input::TurbulenceReferenceLengthScale L_turb
	{
		data_->cref<input::Chord>(),
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
		std::move(epsilon),
		std::move(L_turb),
		std::move(nut),
		std::move(omega)
	);
}


void Airfoil::design()
{
	// first simple design loop
	// loop
	// 		run sim
	// 		compute stagger angle correction
	// 		rebuild

	auto& xi {data_->ref<input::StaggerAngle>()};
	input::StaggerAngle xi_new {xi.value()};	// dummy
	while
	(
		isGreaterOrEqual
		(
			std::abs
			(
				xi_new.value() - data_->cref<input::StaggerAngle>().value()
			),
			eps
		)
	)
	{
		data_->cref<input = ;

	}
}


Sptr<mesh::ProfileMesh> Airfoil::mesh(const bool writeMesh) const
{
	Sptr<mesh::ProfileMesh> mesh
	{
		new mesh::ProfileMesh {*data_, model_, cwd_}
	};
	mesh->build(profile);

	if (writeMesh)
		mesh->write();

	return mesh;
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
		},
		input::InletRefPoint
		{
			data_->cref<input::Chord>(),
			data_->cref<input::RelMeshSize>(),
			data_->cref<input::SectionExtensionFactor>(),
			profile.lePoint()
		}
	);

	simulation::Simulator sim {*data_, simId_, cwd_};

	if (!mesh)
		mesh = this->mesh();

	mesh->setCwd(sim.caseDirectory);
	mesh->write();

	sim.simulate();
	++simId_;

	return sim.caseDirectory;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
