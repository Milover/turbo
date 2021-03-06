/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::math::BezierCurve

Description
	BezierCurve class.

\*---------------------------------------------------------------------------*/

#ifndef MATH_BEZIER_CURVE_H
#define MATH_BEZIER_CURVE_H

#include <array>
#include <type_traits>

#include "BiCoeff.h"
#include "Error.h"
#include "General.h"
#include "MathGeneral.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace math
{

/*---------------------------------------------------------------------------*\
						Class BezierCurve Definition
\*---------------------------------------------------------------------------*/

template<Integer n, typename T = Vector>
class BezierCurve
{
private:

	static_assert(n > 0);

	// Member functions

		//- Compute value at 't'
		template<Integer k = 0>
		constexpr T compute(const Float t) noexcept;


public:

	using value_type = T;

	// Public data

		inline static constexpr Integer order {n};
		const std::array<const T, n + 1> points;


	// Constructors

		//- Construct from control points
		template
		<
			typename... Points,
			typename = std::enable_if_t
			<
				(std::is_same_v<T, removeCVRef_t<Points>> && ...)
			>
		>
		constexpr BezierCurve(Points&&... ps) noexcept;


	// Member operators

		//- Call operator
		constexpr T operator()(const Float t);

};


// * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * * * //

template<Integer n, typename T>
template<Integer k>
constexpr T BezierCurve<n, T>::compute(const Float t) noexcept
{
	auto term = [&]() constexpr -> T
	{
		return BiCoeff_v<n, k>
			 * pow<n - k>(1.0 - t)
			 * pow<k>(t)
			 * this->points[k];
	};

	if constexpr (k == n)
		return term();
	else
		return this->compute<k + 1>(t) + term();
}


// * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * //

template<Integer n, typename T>
template<typename... Points, typename>
constexpr BezierCurve<n, T>::BezierCurve(Points&&... ps) noexcept
:
	points {std::forward<Points>(ps)...}
{
	static_assert(sizeof...(ps) == n + 1);
}


// * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * * * //

template<Integer n, typename T>
constexpr T BezierCurve<n, T>::operator()(const Float t)
{
	if (!isInRange(t, 0.0, 1.0))
		error(FUNC_INFO, "parameter t out of range [0, 1]");

	return this->compute<>(t);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace math
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
