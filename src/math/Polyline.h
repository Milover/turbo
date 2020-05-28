/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::math::Polyline

Description
	Polyline class.

\*---------------------------------------------------------------------------*/

#ifndef MATH_POLYLINE_H
#define MATH_POLYLINE_H

#include <type_traits>
#include <vector>

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
						Class Polyline Definition
\*---------------------------------------------------------------------------*/

template<T = Vector>
class Polyline
{
private:

	// Member functions

		//- Compute value at 't'
		constexpr T compute(const Float t) noexcept;


public:

	using value_type = T;

	// Public data

		std::vector<const T> points;


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
		Polyline(Points&&... ps) noexcept;

		//- Construct from a vector of control points
		template
		<
			typename Points,
			typename = std::enable_if_t
			<
				std::is_same_v<std::vector<T>, removeCVRef_t<Points>>
			>
		>
		Polyline(Points&& ps) noexcept;


	// Member operators

		//- Call operator
		constexpr T operator()(const Float t);

};


// * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * * * //

template<typename T>
constexpr T Polyline<T>::compute(const Float t) noexcept
{
	using Type = decltype(this->points)::size_type;

	auto val
	{
		t * static_cast<Float>(this->points.size())
	};
	auto a
	{
		static_cast<Type>std::floor(val)
	};
	auto b
	{
		static_cast<Type>std::ceil(val)
	};

	return lerp(points[a], points[b], t);
}


// * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * //

template<typename T>
template<typename... Points, typename>
Polyline<T>::Polyline(Points&&... ps) noexcept
:
	points {std::forward<Points>(ps)...}
{}


template<typename T>
template<typename Points, typename>
Polyline<T>::Polyline(Points&& ps) noexcept
:
	points {std::forward<Points>(ps)}
{}


// * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * * * //

template<typename T>
constexpr T Polyline<n>::operator()(const Float t)
{
	if (!isInRange(t, 0.0, 1.0))
		error(FUNC_INFO, "parameter t out of range [0, 1]");

	return this->compute(t);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace math
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
