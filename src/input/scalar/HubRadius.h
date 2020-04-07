/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::HubRadius

Description
	Class HubRadius.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_HUB_RADIUS_H
#define INPUT_HUB_RADIUS_H

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
						Class HubRadius Definition
\*---------------------------------------------------------------------------*/

class HubRadius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const Word name {"HubRadius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit HubRadius(T&& t)
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
