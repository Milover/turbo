/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <deque>
#include <filesystem>
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

void Airfoil::adjustCamberAngle()
{

}


void Airfoil::adjustStaggerAngle()
{
	if (pressureCheck())
		return;

	// FIXME: if we're restarting we should grab 'delay' previous sim results
	const auto delay {11ul};			// XXX: user input or something?
	Float increment;

	std::deque<Uptr<SimData>> simCache;
	std::deque<input::StaggerAngle> xiCache;
	while (true)
	{
		build();

		auto& dpReq {data_->ref<input::TargetTotalPressureDifference>()};
		auto& xiStep {data_->ref<input::StaggerAngleDesignPrecision>()};
		auto& xi {data_->ref<input::StaggerAngle>()};

		xiCache.emplace_back(xi);
		simCache.emplace_back
		(
			new SimData {simulate()}
		);
		postprocess(*simCache.back());

		// stop if we've reached target pressure
		if
		(
			pressureCheck
			(
				*simCache.back()->dpTot,
				data_->cref<input::DesignPressureRelTolerance>()
			)
		)
		{
			writer_->writeComment("target pressure satisfied");
			break;
		}

		bool lessThan
		{
			!isGreaterOrEqual
			(
				simCache.back()->dpTot->value(),
				dpReq.value()
			)
		};

		// start checking whether we've passed the min/max pressure after an
		// initial delay, we require the pressure to be decreasing/increasing
		// for 'delay - 1' consecutive iterations for us to stop searching
		if (simCache.size() == delay)
		{
			bool decrIncr {true};

			if (lessThan)
				for (auto it {simCache.begin() + 1}; it != simCache.end(); ++it)
				{
					decrIncr = decrIncr
							 && !isLessOrEqual
							 	(
									simCache.front()->dpTot->value(),
									(*it)->dpTot->value()
								);
					++it;
				}
			else
				for (auto it {simCache.begin() + 1}; it != simCache.end(); ++it)
				{
					decrIncr = decrIncr
							 && !isGreaterOrEqual
							 	(
									simCache.front()->dpTot->value(),
									(*it)->dpTot->value()
								);
					++it;
				}

			if (decrIncr)
			{
				// remove redundant cases
				for (auto it {simCache.begin() + 1}; it != simCache.end(); ++it)
					std::filesystem::remove_all((*it)->simDir);

				simCache.back().reset
				(
					simCache.front().release()
				);
				xi = xiCache.front();
				build();

				if (lessThan)
					writer_->writeComment
					(
						"target pressure not satisfied, "
						"max pressure achieved in case: ",
						simCache.back()->simId
					);
				else
					writer_->writeComment
					(
						"target pressure not satisfied, "
						"min pressure achieved in case: ",
						simCache.back()->simId
					);
				break;
			}

			xiCache.pop_front();
			simCache.pop_front();
		}

		// increment/decrement stagger and rerun
		if (simCache.size() < 2)
		{
			if (lessThan)
				increment = xiStep.value();
			else
				increment = -xiStep.value();
		}
		else
		{
			auto dp {(*simCache.rbegin())->dpTot->value()};
			auto dpOld {(*(simCache.rbegin() + 1))->dpTot->value()};

			if
			(
				lessThan && dpOld < dpReq.value()
			)
				increment = std::abs(increment);
			else if
			(
				!lessThan && dpOld > dpReq.value()
			)
				increment = -std::abs(increment);
			else
			{
				auto xiOld {(xiCache.rbegin() + 1)->value()};

				increment = math::interpolate
							(
								dpReq.value(),
								dpOld,
								dp,
								xiOld,
								xi.value()
							)
						  - xi.value();
			}
		}

		xi.set(xi.value() + increment);
	}

	postprocess(*simCache.back(), false, true);
	writer_->flush();
}


void Airfoil::alignStagnationPoint(DesignData& dd)
{
	build();
	data_->ref<input::StaggerAngle>().correct
	(
		dd.staggerAngleAlignment
	);

	while (true)
	{
		build();
		auto sd {simulate()};

		postprocess(sd);
		sd.stagnationPoint->z() = profile.radius();

		auto& xi {data_->ref<input::StaggerAngle>()};
		xi.correct
		(
			*sd.stagnationPoint,
			profile.lePoint(),
			profile.centroid()
		);

		if
		(
			xi.tolerance
			(
				data_->cref<input::StaggerAngleDesignPrecision>().value()
			)
		)
		{
			xi.revert();
			flagPath(sd.simDir, ".aligned");

			designData.empty = false;
			designData.totalStaggerCorr = xi.totalCorrection();

			writer_->writeComment("alignment done");
			writer_->flush();

			break;
		}
	}
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
	input::CamberAngleScalingFactor camberScale
	{
		data_->cref<input::CamberAngleScalingFactorDistribution>().valueAt(rRel)
	};
	input::CamberAngle camber
	{
		data_->cref<input::InletVelocity>(),
		c_2,
		U,
		camberScale
	};

	// store
	input::storeAll
	(
		*data_,
		std::move(c_2),
		std::move(camber),
		std::move(camberScale),
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
			data_->cref<input::StaggerAngle>().value(),
			simData.c_2->value().y(),
			simData.dp->value(),
			simData.dpTot->value(),
			simData.eta->value()
		);
		writer_->flush();

		profile.writeCsv(simData.simDir / "profile.csv");
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
			"stagger",
			"swirl_2",
			"pressure",
			"tot. pressure",
			"eta"
		);
		writer_->flush();
	}

	// design the airfoil
	if (restarted())
		writer_->writeComment("restarting");

	if (!std::filesystem::exists(cwd_ / "ALIGNED"))
	{
		// FIXME: implement a dedicated messaging system
		std::cout << "aligning stagnation point: " << filename.stem() << '\n';
		alignStagnationPoint(dd);
	}

	// FIXME: implement a dedicated messaging system
	std::cout << "adjusting camber angle: " << filename.stem() << '\n';
	adjustCamberAngle();

	// FIXME: implement a dedicated messaging system
	std::cout << "adjusting stagger angle: " << filename.stem() << '\n';
	adjustStaggerAngle();

	dumpData();
	designed_ = true;
	dd.empty = false;

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


Airfoil::SimData Airfoil::simulate()
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
