/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Airfoil

Description
	Class Airfoil

	WARNING:
		Restarting (of any kind) is untested.

SourceFiles
	Airfoil.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_AIRFOIL_H
#define DESIGN_AIRFOIL_H

#include <deque>
#include <type_traits>
#include <utility>

#include "CsvReader.h"
#include "CsvWriter.h"
#include "General.h"
#include "Profile.h"
#include "ProfileMesh.h"
#include "Registry.h"
#include "TurboBase.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class Airfoil Declaration
\*---------------------------------------------------------------------------*/

class Airfoil final
:
	public TurboBase
{
public:

	// Member classes

		//- Data returned from the design process
		//	NOTE: currently completely useless
		struct DesignData
		{
			// Public data

				bool empty {true};

				Float staggerAngleAlignment {0.0};

			// Constructors

				//- Default constructor
				//	NOTE: see C++ issue 1360 and 1397
				constexpr DesignData() noexcept
				{};
		};


		//- Data returned from the simulation
		//	NOTE: only handles steady state simulations
		struct SimData
		{
			// Public data

				std::size_t simId;
				Path simDir;

				Uptr<std::size_t> time;
				Uptr<input::StaticPressureDifference> dp;
				Uptr<input::OutletRelativeVelocity> w_2;
				Uptr<input::AirfoilTotalForce> fTot;
				Uptr<input::OutletVelocity> c_2;
				Uptr<input::TotalPressureDifference> dpTot;
				Uptr<input::AirfoilEfficiency> eta;
				Uptr<Vector> stagnationPoint;

			// Constructors

				//- Construct by reading the simulation files
				inline SimData
				(
					const std::size_t id,
					const Path& simDirectory,
					const input::Registry& reg
				);
		};


private:

	// Private data

		bool designed_ {false};
		std::size_t simId_ {0};
		Uptr<CsvWriter> writer_;


	// Member functions

		//- Iteratively adjust a parameter such that the total pressure
		//	is either the target total pressure or the maximum achievable.
		//	Does nothing is existing total pressure is greater or equal
		//	to target total pressure. Currently supports adjusting the
		//	camber and stagger angle.
		template<typename Param>
		void adjustParameter(Pair<Float> limits);

		//- Iteratively adjust stagger angle such that the stagnation point
		//	is aligned with LE
		void alignStagnationPoint
		(
			DesignData& dd,
			bool flagOnFinish = true
		);

		//- Iteratively adjust stagger angle such that the stagnation point
		//	is aligned with LE, don't store design data or flag when done
		void alignStagnationPoint();

		//- Compute and store turbulence properties
		void computeTurbulence() const;

		//- Construct the component
		void construct(const input::Radius& radius);

		//- Load data from the last state of the previous design process
		void loadLastState();

		//- Postprocess simulation results
		void postprocess
		(
			const SimData& simData,
			const bool write = true,
			const bool store = false
		) const;


public:

	// Public data

		Profile profile;


	// Constructors

		//- Default construct from a station number,
		//	creates an owned registry and creates a model
		explicit Airfoil
		(
			const input::Radius& radius,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		Airfoil
		(
			const input::Radius& radius,
			const input::Registry& reg,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename T>
		Airfoil
		(
			const input::Radius& radius,
			const input::Registry& reg,
			T&& model,
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);


	// Member functions

		//- Build geometry
		void build(Profile&& p = Profile {});

		//- Create an Airfoil that satisfies the total pressure difference,
		//	use supplied design data if available
		//	FIXME: see .cpp file
		DesignData design(const DesignData& supplied = DesignData {});

		//- Check if design has been completed
		[[nodiscard]] bool designed() const noexcept;

		//- Build mesh
		Sptr<mesh::ProfileMesh> mesh(const bool writeMesh = false) const;

		//- Check if existing total pressure difference satisfies target
		//	total pressure
		[[nodiscard]] bool pressureCheck() const;

		//- Check if 'dpTot' satisfies the target total pressure
		[[nodiscard]] bool pressureCheck
		(
			const input::TotalPressureDifference& dpTot,
			const input::DesignPressureRelTolerance& tol
		) const;

		//- Prep and run simulation, return the simulation data
		[[maybe_unused]] SimData simulate();

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

// FIXME: this is a provisional implementation and should be rewriten
template<typename Param>
void Airfoil::adjustParameter(Pair<Float> limits)
{
	static_assert
	(
		std::is_same_v<input::CamberAngle, Param>
	 || std::is_same_v<input::StaggerAngle, Param>
	);

	if (pressureCheck())
		return;

	// FIXME: if we're restarting we should grab 'delay' previous sim results
	const auto delay {11ul};			// XXX: user input or something?
	Float increment;

	std::deque<Uptr<SimData>> simCache;
	std::deque<Param> paramCache;
	Float paramStep;

	for (auto i {0ul}; i < data_->cref<input::MaxDesignIter>().value(); ++i)
	{
		build();

		if (paramCache.empty())
		{
			if constexpr (std::is_same_v<input::CamberAngle, Param>)
			{
				paramStep = data_->cref<input::CamberAngle>().value()
						  * data_->cref<input::CamberAngleRelDesignPrecision>().value();

				writer_->writeComment("adjusting camber angle");
			}
			else if constexpr (std::is_same_v<input::StaggerAngle, Param>)
			{
				paramStep = data_->cref<input::StaggerAngle>().value()
						  * data_->cref<input::StaggerAngleRelDesignPrecision>().value();

				writer_->writeComment("adjusting stagger angle");
			}
		}

		auto& dpReq {data_->cref<input::TargetTotalPressureDifference>()};
		auto& param {data_->ref<Param>()};

		paramCache.emplace_back(param);
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

		// check if the difference between the current and the required
		// value is bigger than the difference between the base and the
		// required value
		auto diffCheck = [](auto&& base, auto&& current, auto&& req) -> bool
		{
			return !isGreaterOrEqual
			(
				std::abs(req - base),
				std::abs(req - current)
			);
		};

		// Start checking whether we're moving toward the required pressure
		// after an initial delay. We require the abs. difference between the
		// simulated pressure and the target pressure to be increasing for
		// 'delay - 1' consecutive iterations for us to stop searching
		if (simCache.size() == delay)
		{
			bool increasing {true};

			for (auto it {simCache.begin() + 1}; it != simCache.end(); ++it)
			{
				increasing = increasing
						  && diffCheck
						  	 (
							 	simCache.front()->dpTot->value(),
								(*it)->dpTot->value(),
								dpReq.value()
							 );
				++it;
			}

			if (increasing)
			{
				// remove redundant cases
				for (auto it {simCache.begin() + 1}; it != simCache.end(); ++it)
					std::filesystem::remove_all((*it)->simDir);

				simCache.back().reset
				(
					simCache.front().release()
				);
				param = paramCache.front();
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

			paramCache.pop_front();
			simCache.pop_front();
		}

		// increment/decrement parameter and rerun
		if (simCache.size() < 2)
		{
			if (lessThan)
				increment = paramStep;
			else
				increment = -paramStep;
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
				auto paramOld {(paramCache.rbegin() + 1)->value()};

				increment = math::interpolate
							(
								dpReq.value(),
								dpOld,
								dp,
								paramOld,
								param.value()
							)
						  - param.value();
			}
		}

		// stop here if we don't intend to simulate afterwards
		if
		(
			i == data_->cref<input::MaxDesignIter>().value() - 1
		)
		{
			writer_->writeComment
			(
				"target pressure not satisfied, max iter reached"
			);
			break;
		}

		// if we've incremented the camber angle and the target pressure
		// hasn't been satisfied, we realign before incrementing again
		if constexpr (std::is_same_v<input::CamberAngle, Param>)
		{
			std::cout << "realigning: " << filename.stem() << '\n';

			writer_->writeComment("realigning");
			writer_->flush();

			alignStagnationPoint();
		}

		// increment and check
		auto tmp {param.value()};
		param.set(param.value() + increment);
		if
		(
			!isInRange(param.value(), limits.first, limits.second)
		)
		{
			param.set(tmp);

			writer_->writeComment
			(
				"target pressure not satisfied, parameter limits reached"
			);
			break;
		}
	}

	postprocess(*simCache.back(), false, true);
	writer_->flush();
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
Airfoil::Airfoil
(
	const input::Radius& radius,
	const input::Registry& reg,
	T&& model,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase
	{
		"airfoil.step",
		reg,
		std::forward<T>(model),
		parentCwd,
		id
	}
{
	construct(radius);
}


/*---------------------------------------------------------------------------*\
						Class SimData Definition
\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Airfoil::SimData::SimData
(
	const std::size_t id,
	const Path& simDirectory,
	const input::Registry& reg
)
:
	simId {id},
	simDir {simDirectory}
{
	input::CsvReader
	<
		Float,		// time
		Float,		// inlet kin. pressure
		Vector		// inlet rel. velocity
	> csvPSFV_i {};
	input::CsvReader
	<
		Float,		// time
		Float,		// outlet kin. pressure
		Vector		// outlet rel. velocity
	> csvPSFV_o {};
	input::CsvReader
	<
		Float,		// time
		String,		// field
		Float,		// min
		Vector,		// location(min)
		Integer,	// processor
		Float,		// max
		Vector,		// location(max)
		Integer		// processor
	> csvFMM {};
	input::CsvReader
	<
		Float,		// time
		Vector,		// total force
		Vector,		// pressure force
		Vector		// viscous force
	> csvForces {};

	// FIXME: files should be read by 'foam-file-objects' once implemented
	csvPSFV_i.read
	(
		simDir
	  / "postProcessing/turbo_patchSurfaceFieldValue_inlet/"
		"0/surfaceFieldValue.dat"
	);
	csvPSFV_o.read
	(
		simDir
	  / "postProcessing/turbo_patchSurfaceFieldValue_outlet/"
		"0/surfaceFieldValue.dat"
	);
	csvFMM.read
	(
		simDir
	  / "postProcessing/turbo_fieldMinMax_p/0/fieldMinMax.dat"
	);
	csvForces.read
	(
		simDir
	  / "postProcessing/turbo_forces/0/force.dat"
	);

	// FIXME: we're assuming a steady state simulation
	time.reset
	(
		new std::size_t
		{
			static_cast<std::size_t>(csvFMM.cref<0>().back())
		}
	);
	dp.reset
	(
		new input::StaticPressureDifference
		{
			reg.cref<input::Density>().value()
		  * (csvPSFV_o.cref<1>().back() - csvPSFV_i.cref<1>().back())
		}
	);
	w_2.reset
	(
		new input::OutletRelativeVelocity {csvPSFV_o.cref<2>().back()}
	);
	fTot.reset
	(
		 new input::AirfoilTotalForce {csvForces.cref<1>().back()}
	);
	c_2.reset
	(
		new input::OutletVelocity
		{
			*w_2,
			reg.cref<input::BladeVelocity>()
		}
	);
	dpTot.reset
	(
		new input::TotalPressureDifference
		{
			reg.cref<input::InletVelocity>(),
			*c_2,
			*dp,
			reg.cref<input::Density>()
		}
	);
	eta.reset
	(
		new input::AirfoilEfficiency
		{
			reg.cref<input::InletVelocity>(),
			reg.cref<input::BladeVelocity>(),
			*fTot,
			*dpTot,
			reg.cref<input::Pitch>()
		}
	);
	stagnationPoint.reset
	(
		new Vector {csvFMM.cref<6>().back()}
	);
}





// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
