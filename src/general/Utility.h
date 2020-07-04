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

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * Constants * * * * * * * * * * * * * * * * //

inline static constexpr Float pi {M_PI};

inline static constexpr Float eps {1e-15};

inline static constexpr char suffixSeparator {'.'};


// * * * * * * * * * * * * * Arithmetic Functions  * * * * * * * * * * * * * //

//- Compare two numbers (up to ``about'' machine precision)
template<typename T>
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
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
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
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
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
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
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
isInRange
(
	T x,
	T min,
	T max,
	Integer ulp = 2
) noexcept
{
	return isGreaterOrEqual(x, min, ulp)
		&& isLessOrEqual(x, max, ulp);
}


//- Check if tolerance 'tol' is satisfied i.e. |a - sign(a)*b| <= tol
template<typename T>
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
tolerance
(
	T a,
	T b,
	T tol,
	Integer ulp = 2
) noexcept
{
	return isLessOrEqual
	(
		std::abs(a - std::copysign(b, a)),
		tol,
		ulp
	);
}


//- Check if rel. tolerance 'tol' is satisfied i.e. |1 - |a/b|| <= tol
template<typename T>
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, bool>
relTolerance
(
	T a,
	T b,
	T tol,
	Integer ulp = 2
) noexcept
{
	return isLessOrEqual
	(
		std::abs(1.0 - std::abs(a / b)),
		tol,
		ulp
	);
}


//- Convert radians to degrees
template<typename T>
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
radToDeg(const T t)
{
	static constexpr Float radDeg {180.0 / pi};

	return t * radDeg;
}


//- Convert degrees to radians
template<typename T>
[[nodiscard]] std::enable_if_t<std::is_floating_point_v<T>, T>
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


//- Add a suffix to a filename, retains the extension
template<typename T>
[[nodiscard]] inline Path addFilenameSuffix
(
	const Path& path,
	T&& suffix
)
{
	auto tmp {path};
	auto filename {path.stem().string()};
	auto extension {path.filename().extension().string()};

	if constexpr (std::is_integral_v<removeCVRef_t<T>>)
	{
		filename = filename
				 + suffixSeparator
				 + std::to_string(std::forward<T>(suffix));
	}
	else
	{
		filename = filename + suffixSeparator + suffix;
	}
	tmp.replace_filename(filename + extension);

	return tmp;
}


//- Flag an existing file or directory by adding an extension i.e.
//	rename 'path' to 'path[extension]'
template<typename T>
inline void flagPath
(
	Path& path,
	T&& extension
)
{
	if (!std::filesystem::exists(path))
		error(FUNC_INFO, "path: ", path, " doesn't exist");

	Path tmp {path};
	path.replace_extension(extension);
	std::filesystem::rename(tmp, path);
}


// * * * * * * * * * * * * * * Input Functions * * * * * * * * * * * * * * * //

//- Read a string, (contiguous block of non-whitespace characters)
[[nodiscard]] inline String readString(std::istream& is)
{
	String s {""};

	while (is)
	{
		char c;
		is.get(c);

		if
		(
			std::iswspace(c)
		 && !s.empty()
		)
			break;
		else if (std::iswspace(c))
			continue;

		s += c;

		if (is.fail())
			error(FUNC_INFO, "error while parsing string");
	};

	return s;
}

// * * * * * * * * * * * * * * Output Functions  * * * * * * * * * * * * * * //

//- Mass print to a stream
template<typename... T>
inline void massPrint
(
	std::ostream& os,
	const String::size_type width,
	const String& delimiter,
	const String& terminator,
	T&&... t
)
{
	static_assert(sizeof...(t) > 0);

	if constexpr
	(
		(std::is_pointer_v<removeCVRef_t<T>> && ...)
	)
	{
		(t->print(os, width, delimiter, terminator), ...);
	}
	else
		(t.print(os, width, delimiter, terminator), ...);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
