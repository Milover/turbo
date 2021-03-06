/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::math::Polyline

Description
	Polyline class.

	WARNING: this guy is probably fucked

\*---------------------------------------------------------------------------*/

#ifndef MATH_POLYLINE_H
#define MATH_POLYLINE_H

#include <algorithm>
#include <cmath>
#include <istream>
#include <ostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "Error.h"
#include "General.h"
#include "List.h"
#include "MathGeneral.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace math
{

// Forward declarations
template<typename T>
class Polyline;


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

//- Check if a type is a Polyline
template<typename T, typename Value = void>
struct isPolyline : std::false_type {};

template<typename T>
struct isPolyline<T, std::void_t<typename removeCVRef_t<T>::value_type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			Polyline<typename removeCVRef_t<T>::value_type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isPolyline_v = isPolyline<T>::value;


/*---------------------------------------------------------------------------*\
						Class Polyline Definition
\*---------------------------------------------------------------------------*/

template<typename T = Vector>
class Polyline
{
private:

	static_assert
	(
		std::is_arithmetic_v<T>
	 || std::is_same_v<Vector, T>
	);

	// Private data

		List<T> points_;


public:

	using container_type = List<T>;
	using value_type = T;


	// Constructors

		//- Default constructor
		Polyline() = default;

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

		//- Construct from a vector/list of control points
		template
		<
			typename Points,
			typename = std::enable_if_t
			<
				std::is_same_v<std::vector<T>, removeCVRef_t<Points>>
			 || std::is_same_v<List<T>, removeCVRef_t<Points>>
			>
		>
		explicit Polyline(Points&& ps) noexcept;


	// Member functions

		//- Get points cref
		[[nodiscard]] const container_type& pointsCRef() const noexcept;

		//- Get points ref
		[[nodiscard]] container_type& pointsRef() noexcept;


	// Member operators

		//- Call operator,
		//	returns piecewise interpolated value at t, where t is in range [0, 1],
		//	clamps if t is out of range
		[[nodiscard]] auto operator()(const Float t) noexcept(ndebug);

};

// * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * * * //

template<typename T>
[[nodiscard]] bool isNan(const Polyline<T>& pl) noexcept(ndebug)
{
	bool nanValue {false};

	for (const auto& p : pl.pointsCRef())
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			nanValue = nanValue || std::isnan(p);
		}
		else if constexpr (std::is_same_v<Vector, T>)
		{
			nanValue = nanValue || isNan(p);
		}
		else
		{
			error(FUNC_INFO, "value type NaN check not implemented");
		}
	}

	return nanValue;
}


// * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * * * * //

//- Input stream operator
template<typename T>
std::istream& operator>>(std::istream& is, Polyline<T>& pl)
{
	is >> pl.pointsRef();

	return is;
}


//- Output stream operator
template<typename T>
std::ostream& operator<<(std::ostream& os, const Polyline<T>& pl)
{
	os << pl.pointsCRef();

	return os;
}


// * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * //

template<typename T>
template<typename... Points, typename>
Polyline<T>::Polyline(Points&&... ps) noexcept
:
	points_ {std::forward<Points>(ps)...}
{}


template<typename T>
template<typename Points, typename>
Polyline<T>::Polyline(Points&& ps) noexcept
:
	points_ {std::forward<Points>(ps)}
{}


// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

template<typename T>
const typename Polyline<T>::container_type&
Polyline<T>::pointsCRef() const noexcept
{
	return this->points_;
}


template<typename T>
typename Polyline<T>::container_type& Polyline<T>::pointsRef() noexcept
{
	return this->points_;
}


// * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * * * //

template<typename T>
auto Polyline<T>::operator()(const Float t) noexcept(ndebug)
{
	if (this->points_.empty())
		error(FUNC_INFO, "polyline is empty");
	else if (this->points_.size() == 1)
		return this->points_.front();

	using SizeType = typename decltype(this->points_)::size_type;

	auto nPts {this->points_.size()};
	Float p {std::clamp(t, 0.0, 1.0)};

	// find upper bound of interval
	auto upper
	{
		static_cast<SizeType>
		(
			std::ceil
			(
				p * static_cast<Float>(nPts)
			)
		)
	};

	// fake clamp
	if (upper <= 0)
		upper = 1;
	else if (upper > nPts - 1)
		upper = nPts - 1;

	// get values at boundaries of inteval
	auto a {this->points_[upper-1]};
	auto b {this->points_[upper]};

	// find value at which to interpolate
	Float p1
	{
		static_cast<Float>(upper) / static_cast<Float>(nPts - 1)
	};

	Float p0;
	if (upper == 1)
		p0 = 0.0;
	else
		p0 = static_cast<Float>(upper - 1) / static_cast<Float>(nPts - 1);

	Float val
	{
		(p - p0) / (p1 - p0)
	};

	return lerp(a, b, val);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace math
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
