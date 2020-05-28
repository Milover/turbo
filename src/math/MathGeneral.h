/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Declarations of general arithmetic equations.

	NOTE:
		- floating point exceptions are not handled/checked

\*---------------------------------------------------------------------------*/

#ifndef COMPUTE_GENERAL_H
#define COMPUTE_GENERAL_H

#include <limits>
#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace math
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Raises a number to the given power
template
<
	Integer n,
	typename T,
	typename = std::enable_if_t<std::is_arithmetic_v<T>>
>
inline constexpr T pow(T t [[maybe_unused]])
{
	if constexpr (n == 0)
	{
		return 1;
	}
	else if constexpr (n < 0)
	{
		return 1 / (t * pow<-n - 1>(t));
	}
	else
	{
		return t * pow<n - 1>(t);
	}
}


//- Linear interpolate, $a + t \cdot (b - a)$,
//	will extrapolate if $t \notin [0, 1]$
template<typename T1, typename T2, typename T3>
inline constexpr auto lerp
(
	const T1 a,
	const T2 b,
	const T3 t
)
{
	return a + t * (b - a);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace math
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
