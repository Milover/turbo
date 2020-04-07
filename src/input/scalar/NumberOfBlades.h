/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::NumberOfBlades

Description
	Class NumberOfBlades.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_NUMBER_OF_BLADES_H
#define INPUT_NUMBER_OF_BLADES_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class NumberOfBlades Definition
\*---------------------------------------------------------------------------*/

class NumberOfBlades final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const Word name {"NumberOfBlades"};


	// Constructors

		//- Construct from a Integer,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit NumberOfBlades(T&& t)
		:
			PVBase {std::forward<T>(t)}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
