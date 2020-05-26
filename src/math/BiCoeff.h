/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::math::BiCoeff

Description
	Binomial coefficient class.

\*---------------------------------------------------------------------------*/

#ifndef MATH_BI_COEFF_H
#define MATH_BI_COEFF_H

#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace math
{

/*---------------------------------------------------------------------------*\
						Class BiCoeff Definition
\*---------------------------------------------------------------------------*/

template<Integer n, Integer k>
struct BiCoeff
{
	static_assert
	(
		n > 0
	 && k > 0
	 && n >= k
	);

	inline static constexpr Integer value
	{
		BiCoeff<n, k - 1>::value * (n + 1 - k) / k
	};
};


template<Integer n>
struct BiCoeff<n, 0>
{
	static_assert(n >= 0);

	inline static constexpr Integer value {1};
};


template<Integer k>
struct BiCoeff<0, k>
{
	static_assert(k == 0);

	inline static constexpr Integer value {1};
};


template<Integer n, Integer k>
inline static constexpr Integer BiCoeff_v = BiCoeff<n, k>::value;



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace math
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
