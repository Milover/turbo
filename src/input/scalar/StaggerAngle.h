/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::StaggerAngle

Description
	Class StaggerAngle.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_STAGGER_ANGLE_H
#define INPUT_STAGGER_ANGLE_H

#include <type_traits>
#include <utility>

#include "BladeVelocity.h"
#include "General.h"
#include "IncidenceAngle.h"
#include "InclinationAngle.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class StaggerAngle Definition
\*---------------------------------------------------------------------------*/

class StaggerAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const Word name {"StaggerAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit StaggerAngle(T&& t)
		:
			RegBase {std::forward<T>(t)}
		{}

		//- Compute and construct
		StaggerAngle
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const InclinationAngle& zeta,
			const IncidenceAngle& i
		)
		:
			StaggerAngle
			{
				compute::computeStaggerAngle
				(
					c_1.value(),
					U.value(),
					zeta.value(),
					i.value()
				)
			}
		{}

		//- Compute assuming zero incidence and construct
		StaggerAngle
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const InclinationAngle& zeta
		)
		:
			StaggerAngle
			{
				compute::computeStaggerAngle
				(
					c_1.value(),
					U.value(),
					zeta.value()
				)
			}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
