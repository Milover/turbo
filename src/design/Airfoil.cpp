/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <deque>
#include <filesystem>
#include <fstream>
#include <utility>
#include <vector>

#include "Airfoil.h"

#include "CsvReader.h"
#include "CsvWriter.h"
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

Airfoil::SimData Airfoil::alignStagnationPoint()
{
	DesignData dd;

	return alignStagnationPoint(dd, false);
}


// FIXME: we should rethink this
Airfoil::SimData Airfoil::alignStagnationPoint
(
	DesignData& dd,
	bool flagOnFinish
)
{
	// use design data if available
	if (!dd.empty)
	{
		build();
		data_->ref<input::StaggerAngle>().correct
		(
			dd.staggerAngleAlignment
		);
	}

	bool initialSign;
	SimData sd;

	for (auto i {0ul}; i < data_->cref<input::MaxDesignIter>().value(); ++i)
	{
		build();
		sd = simulate();

		postprocess(sd);
		sd.stagnationPoint->z() = profile.radius();

		auto& xi {data_->ref<input::StaggerAngle>()};
		xi.correct
		(
			*sd.stagnationPoint,
			profile.lePoint(),
			profile.centroid()
		);

		// we'll stop once we overshoot
		if (i == 0)
			initialSign = std::signbit(xi.correction());

		if
		(
			xi.tolerance
			(
				data_->cref<input::StagnationPointDesignPrecision>().value()
			)
		 || initialSign != std::signbit(xi.correction())
		)
		{
			xi.revert();
			writer_->writeComment("alignment done");

			break;
		}
		else if
		(
			i == data_->cref<input::MaxDesignIter>().value() - 1
		)
			writer_->writeComment
			(
				"alignment didn't finish, max iter reached"
			);
	}

	// we generally don't want to run this more than once
	// so we flag that we've done it already even if
	// we haven't aligned properly
	if (flagOnFinish)
		std::ofstream {cwd_ / "ALIGNED"};

	dd.empty = false;
	dd.staggerAngleAlignment = data_->cref<input::StaggerAngle>().totalCorrection();

	writer_->flush();

	return sd;
}


void Airfoil::construct(const input::Radius& radius)
{
	input::RelRadius rRel
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
		data_->cref<input::BladeEfficiency>(),
		data_->cref<input::Density>()
	};
	input::KinematicPressureDifference dpKin
	{
		dp,
		data_->cref<input::Density>()
	};
	input::TargetTotalPressureDifference dpTotReq
	(
		input::TargetTotalPressureDifference
		{
			c_2,
			U,
			data_->cref<input::BladeEfficiency>(),
			data_->cref<input::Density>()
		}
	);

	// geometry
	input::Solidity solidity
	{
		data_->cref<input::SolidityDistribution>().valueAt(rRel)
	};
	input::Pitch pitch
	{
		data_->cref<input::NumberOfBlades>(),
		radius
	};
	input::CamberAngle camber
	{
		data_->cref<input::InletVelocity>(),
		c_2,
		U
	};

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(dp),
		std::move(dpKin),
		std::move(dpTotReq),
		std::move(pitch),
		radius,
		std::move(rRel),
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
				cref<input::MaxAbsBladeThicknessDistribution>().valueAt(rRel)
			}
		);
	if (data_->has<input::MaxPassageWidthDistribution>())
		data_->store
		(
			input::MaxPassageWidth
			{
				data_->cref<input::MaxPassageWidthDistribution>().valueAt(rRel)
			}
		);

	if (restarted())
		loadLastState();
}


void Airfoil::loadLastState()
{
	StringConverter<std::size_t> converter;

	Pair<std::size_t, Path> lastCase {0, {}};

	// find the relevant directories
	for (Path p : std::filesystem::directory_iterator(cwd_))
	{
		if (std::filesystem::is_directory(p))
		{
			auto tmp {p.extension().string()};
			tmp.erase(0, 1);
			auto simId {converter(tmp)};

			if (simId >= lastCase.first)
			{
				lastCase.first = simId;
				lastCase.second = p;
			}
		}
	}
	if (lastCase.second.empty())
		return;

	build
	(
		Profile {lastCase.second / "profile.csv"}
	);
	simId_ = lastCase.first + 1;

	SimData sd
	{
		lastCase.first,
		lastCase.second,
		*data_
	};
	postprocess(sd, false, true);
}


void Airfoil::postprocess
(
	const SimData& simData,
	const bool write,
	const bool store
) const
{
	// write design iteration data
	if (write)
	{
		writer_->write
		(
			simData.simId,
			*simData.time,
			data_->cref<input::Chord>().value(),
			data_->cref<input::CamberAngle>().value(),
			data_->cref<input::StaggerAngle>().value(),
			simData.c_2->value().y(),
			simData.dp->value(),
			simData.dpTot->value(),
			simData.eta->value()
		);
		writer_->flush();
	}

	// store to registry
	if (store)
		input::storeAll
		(
			*data_,
			*simData.dp,
			*simData.w_2,
			*simData.fTot,
			*simData.c_2,
			*simData.dpTot,
			*simData.eta
		);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::Airfoil
(
	const input::Radius& radius,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"airfoil.step", parentCwd, id}
{
	construct(radius);
}


Airfoil::Airfoil
(
	const input::Radius& radius,
	const input::Registry& reg,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase {"airfoil.step", reg, parentCwd, id}
{
	construct(radius);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Airfoil::build(Profile&& p)
{
	if (p.empty())
	{
		// compute/recompute because we always try to satisfy the solidity
		data_->store<input::Chord>
		(
			input::Chord
			{
				data_->cref<input::Pitch>(),
				data_->cref<input::Solidity>()
			}
		);

		// we need the basic geometry to compute the stagger
		ProfileGenerator generator {*data_};

		// compute if this is the first build
		if (!data_->has<input::StaggerAngle>())
			data_->store
			(
				input::StaggerAngle
				{
					data_->cref<input::InletVelocity>(),
					data_->cref<input::BladeVelocity>(),
					input::InclinationAngle
					{
						generator.inclination(0.0)	// leading edge inclination
					}
				}
			);

		// now we can build the profile
		profile.build(generator, *data_);
	}
	// we might be restarting
	else
	{
		if (p.wrapped())
			p.unwrap();

		profile = std::move(p);
		data_->store
		(
			input::CamberAngle {profile.camberAngle()}
		);
		data_->store
		(
			input::StaggerAngle {profile.staggerAngle()}
		);
	}

	input::Chord chord
	{
		profile.chord()
	};
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
		std::move(chord),
		std::move(epsilon),
		std::move(L_turb),
		std::move(nut),
		std::move(omega)
	);
}


// FIXME:
// 		Implement:
// 			Foam files (atleast function object files) should be classes which
// 			should know what kind of data the function object generates,
// 			the file name wherein the data will be written and a way of
// 			extracting relevant data (we generally know what we want to extract
// 			from each function object file), because doing it raw like this
// 			makes the code super hard to read and is probably unmanagable in
// 			the long run. Probably smart to implement this via the 'Simulator'.
Airfoil::DesignData Airfoil::design(const DesignData& supplied)
{
	if (std::filesystem::exists(cwd_ / "SKIP"))
	{
		std::cout << "skipping: " << filename.stem() << '\n';

		if (profile.empty())
			build();

		dumpData();
		designed_ = true;

		return supplied;
	}

	auto dd {supplied};
	designed_ = false;

	Path designFile {cwd_ / "design.csv"};
	if (std::filesystem::exists(designFile))
		writer_.reset
		(
			new CsvWriter {designFile, std::ios::app}
		);
	else
	{
		writer_.reset
		(
			new CsvWriter {designFile}
		);
		writer_->writeHeader
		(
			"sim",
			"iter",
			"chord",
			"camber",
			"stagger",
			"swirl_2",
			"pressure",
			"tot. pressure",
			"eta"
		);
		writer_->flush();
	}

	// dump the initial data
	dumpData();

	// design the airfoil
	if (restarted())
		writer_->writeComment("restarting");

	if (!std::filesystem::exists(cwd_ / "ALIGNED"))
	{
		// FIXME: implement a dedicated messaging system
		std::cout << "aligning stagnation point: " << filename.stem() << '\n';
		alignStagnationPoint(dd);
	}

	Pair<Float> limits;

	// FIXME: implement a dedicated messaging system
	std::cout << "adjusting camber angle: " << filename.stem() << '\n';

	limits.first = 0.0;
	limits.second = data_->cref<input::CamberAngle>().value()
				  * data_->cref<input::CamberAngleDesignLimit>().value();
	adjustParameter<input::CamberAngle>(limits);

	// FIXME: implement a dedicated messaging system
	std::cout << "adjusting stagger angle: " << filename.stem() << '\n';

	limits.first = 0.0;
	limits.second = 0.5 * pi;
	adjustParameter<input::StaggerAngle>(limits);

	dumpData();

	return dd;
}


bool Airfoil::designed() const noexcept
{
	return designed_;
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


bool Airfoil::pressureCheck() const
{
	return data_->has(input::TotalPressureDifference::name)
		&& pressureCheck
		(
			data_->cref<input::TotalPressureDifference>(),
			data_->cref<input::DesignPressureRelTolerance>()
		);
}


bool Airfoil::pressureCheck
(
	const input::TotalPressureDifference& dpTot,
	const input::DesignPressureRelTolerance& tol
) const
{
	return relTolerance
	(
		dpTot.value(),
		data_->cref<input::TargetTotalPressureDifference>().value(),
		tol.value()
	);
}


Airfoil::SimData Airfoil::simulate(bool writeProfile)
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

	if (writeProfile)
		profile.writeCsv(sim.caseDirectory / "profile.csv");

	auto mesh {this->mesh()};
	mesh->setCwd(sim.caseDirectory);
	mesh->write();

	sim.simulate();

	// read files and postprocess
	SimData sd
	{
		simId_,
		sim.caseDirectory,
		*data_
	};

	++simId_;

	return sd;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
