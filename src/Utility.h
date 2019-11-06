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

#include <cmath>
#include <limits>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Typedefs
typedef std::map<std::string, std::string> Stringmap;


//- Vector of pairs template alias
template<typename T>
using Vectorpair = std::vector<std::pair<T, T>>;


//- Static cast (enum class) to underlying type
template <typename T>
constexpr auto toUnderlying(T t) noexcept
{
	return static_cast<typename std::underlying_type_t<T>>(t);
}


//- Compare two numbers (up to ''about`` machine precision)
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
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
		std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
