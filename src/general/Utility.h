/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Some utilities.

\*---------------------------------------------------------------------------*/

#ifndef UTILITY_H
#define UTILITY_H

#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>
#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * //

static constexpr Float pi {M_PI};

static constexpr char filenameSeparator {'_'};


// * * * * * * * * * * * * * Arithmetic Functions  * * * * * * * * * * * * * //

//- Compare two numbers (up to ``about'' machine precision)
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, bool>
isEqual
(
	T x,
	T y,
	Integer ulp = 2
) noexcept
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
std::enable_if_t<std::is_floating_point_v<T>, bool>
isLessOrEqual
(
	T x,
	T y,
	Integer ulp = 2
) noexcept
{
	return x < y || isEqual(x, y, ulp);
}


//- Check if 'x' is greater or equal to 'y'
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, bool>
isGreaterOrEqual
(
	T x,
	T y,
	Integer ulp = 2
) noexcept
{
	return x > y || isEqual(x, y, ulp);
}


//- Check if 'x' is in range [min, max] (inclusive)
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, bool>
isInRange
(
	T x,
	T min,
	T max,
	Integer ulp = 2
) noexcept
{
	return isGreaterOrEqual(x, min, ulp) &&
		   isLessOrEqual(x, max, ulp);
}


//- Convert radians to degrees
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T>
radToDeg(const T t)
{
	static constexpr Float radDeg {180.0 / pi};

	return t * radDeg;
}


//- Convert degrees to radians
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T>
degToRad(const T t)
{
	static constexpr Float degRad {pi / 180.0};

	return t * degRad;
}


// * * * * * * * * * * * * * Formatting Functions  * * * * * * * * * * * * * //

//- Trim leading whitespace (left trim)
inline void trimWhiteL(String& s)
{
	s.erase
	(
		s.begin(),
		std::find_if
		(
			s.begin(),
			s.end(),
			[](int ch) { return !std::isspace(ch); }
		)
	);
}


//- Trim trailing whitespace (right trim)
inline void trimWhiteR(String& s)
{
	s.erase
	(
		std::find_if
		(
			s.rbegin(),
			s.rend(),
			[](int ch) { return !std::isspace(ch); }
		).base(),
		s.end()
	);
}


//- Trim leading and trailing whitespace (left-right trim)
inline void trimWhiteLR(String& s)
{
	trimWhiteL(s);
	trimWhiteR(s);
}


//- Add a prefix to a filename in path
inline void addFilenamePrefix
(
	Path& path,
	const String& prefix
)
{
	auto filename {path.filename().string()};

	filename = prefix + filenameSeparator + filename;

	path.replace_filename(filename);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
