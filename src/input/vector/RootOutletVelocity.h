/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RootOutletVelocity

Description
	Class RootOutletVelocity.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_ROOT_OUTLET_VELOCITY_H
#define INPUT_ROOT_OUTLET_VELOCITY_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "RegistryObject.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class RootOutletVelocity Definition
\*---------------------------------------------------------------------------*/

class RootOutletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const Word name {"RootOutletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Vector, T>, int> = 0>
		>
		explicit RootOutletVelocity(T&& t)
		:
			RegBase {std::forward<T>(t)}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
