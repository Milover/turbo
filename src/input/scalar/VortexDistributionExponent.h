/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::VortexDistributionExponent

Description
	Class VortexDistributionExponent.
	Limited to [-1, 1], where

	   -1 - free vortex distribution
		0 - const. vortex distribution
		1 - forced vortex distribution
	
	Free vortex distribution (value of -1) is assumed by default.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VORTEX_DISTRIBUTION_EXPONENT_H
#define INPUT_VORTEX_DISTRIBUTION_EXPONENT_H

#include <type_traits>
#include <utility>

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class VortexDistributionExponent Definition
\*---------------------------------------------------------------------------*/

class VortexDistributionExponent final
:
	public LimitedValue<Float, -1, 1>
{
public:

	// Public static data

		inline static const Word name {"VortexDistributionExponent"};


	// Constructors

		//- Default constructor
		VortexDistributionExponent() noexcept
		:
			LVBase {-1.0}
		{}

		//- Construct from a Float,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		explicit VortexDistributionExponent(T&& t)
		:
			LVBase {std::forward<T>(t)}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
