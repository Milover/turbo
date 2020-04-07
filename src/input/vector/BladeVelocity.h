/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BladeVelocity

Description
	Class BladeVelocity.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BLADE_VELOCITY_H
#define INPUT_BLADE_VELOCITY_H

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
						Class BladeVelocity Definition
\*---------------------------------------------------------------------------*/

class BladeVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const Word name {"BladeVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Vector, T>, int> = 0>
		>
		explicit BladeVelocity(T&& t)
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
