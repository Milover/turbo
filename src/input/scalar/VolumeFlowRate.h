/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::VolumeFlowRate

Description
	Class VolumeFlowRate.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VOLUME_FLOW_RATE_H
#define INPUT_VOLUME_FLOW_RATE_H

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
						Class VolumeFlowRate Definition
\*---------------------------------------------------------------------------*/

class VolumeFlowRate final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const Word name {"VolumeFlowRate"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit VolumeFlowRate(T&& t)
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
