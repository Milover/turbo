/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InletVelocity

Description
	Class InletVelocity.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INLET_VELOCITY_H
#define INPUT_INLET_VELOCITY_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "HubRadius.h"
#include "InitialDesign.h"
#include "RegistryObject.h"
#include "ShroudRadius.h"
#include "Vector.h"
#include "VolumeFlowRate.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class InletVelocity Definition
\*---------------------------------------------------------------------------*/

class InletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const Word name {"InletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Vector, T>, int> = 0>
		>
		explicit InletVelocity(T&& t)
		:
			RegBase {std::forward<T>(t)}
		{}

		//- Compute and construct
		InletVelocity
		(
			const VolumeFlowRate& Q,
			const HubRadius& r_h,
			const ShroudRadius& r_s
		)
		:
			InletVelocity
			{
				compute::computeInletVelocity
				(
					Q.value(),
					r_h.value(),
					r_s.value()
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
