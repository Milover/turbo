/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InclinationAngle

Description
	Class InclinationAngle.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INCLINATION_ANGLE_H
#define INPUT_INCLINATION_ANGLE_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class InclinationAngle Definition
\*---------------------------------------------------------------------------*/

class InclinationAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const Word name {"InclinationAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit InclinationAngle(T&& t)
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
