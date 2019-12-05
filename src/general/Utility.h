/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Alias templates, typedefs and some other utilities

\*---------------------------------------------------------------------------*/

#ifndef UTILITY_H
#define UTILITY_H

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * //

static constexpr double pi {M_PI};


// * * * * * * * * * * * * * * * * * Enums * * * * * * * * * * * * * * * * * //

enum class InputType
{
	CONST,
	AUTO,
	FROM_FILE
};


// * * * * * * * * * * * * * * * * Typedefs  * * * * * * * * * * * * * * * * //

typedef std::array<double, 3> PointCoordinates;


// * * * * * * * * * * * * * * Template Aliases  * * * * * * * * * * * * * * //

template<typename T>
using Vectorpair = std::vector<std::pair<T, T>>;


template<typename T>
using Ptrvector = std::vector<std::unique_ptr<T>>;


template<typename T = std::string>
using Stringmap = std::map<std::string, T>;


// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Compare two numbers (up to ``about'' machine precision)
template<typename T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
isEqual
(
	T x,
	T y,
	int ulp = 2
)
{
	// the machine epsilon has to be scaled to the magnitude
	// of the values used and multiplied by the desired precision
	// in ULPs (units in the last place)
	return std::abs(x - y) <=
		std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}


//- Check if 'x' is less or equal to 'y'
template<typename T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
isLessOrEqual
(
	T x,
	T y,
	int ulp = 2
)
{
	return x < y || isEqual(x, y, ulp);
}


//- Check if 'x' is greater or equal to 'y'
template<typename T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
isGreaterOrEqual
(
	T x,
	T y,
	int ulp = 2
)
{
	return x > y || isEqual(x, y, ulp);
}


//- Check if 'x' is in range [min, max] (inclusive)
template<typename T>
std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
isInRange
(
	T x,
	T min,
	T max,
	int ulp = 2
)
{
	return isGreaterOrEqual(x, min, ulp) ||
		   isLessOrEqual(x, max, ulp);
}


//- Convert radians to degrees
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T>
radToDeg(const T t)
{
	return t * 180.0 / pi;
}


//- Convert degrees to radians
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T>
degToRad(const T t)
{
	return t * pi / 180.0;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
