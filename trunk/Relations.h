/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Definitions of relational operators defined via the '<' operator.
	No 'NaN' handling, is should be handled locally.

	Inherit from the 'tag' struct to enable.

\*---------------------------------------------------------------------------*/

#ifndef RELATIONS_H
#define RELATIONS_H

#include <type_traits>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace relations
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

struct tag {};


template <typename T>
std::enable_if_t<std::is_base_of_v<tag, T>, bool>
operator==(const T& lhs, const T& rhs)
{
	return !(rhs < lhs) && !(lhs < rhs);
}


template <typename T>
std::enable_if_t<std::is_base_of_v<tag, T>, bool>
operator!=(const T& lhs, const T& rhs)
{
	return !(lhs == rhs);
}


template <typename T>
std::enable_if_t<std::is_base_of_v<tag, T>, bool>
operator>(const T& lhs, const T& rhs)
{
	return rhs < lhs;
}


template <typename T>
std::enable_if_t<std::is_base_of_v<tag, T>, bool>
operator<=(const T& lhs, const T& rhs)
{
	return !(rhs < lhs);
}


template <typename T>
std::enable_if_t<std::is_base_of_v<tag, T>, bool>
operator>=(const T& lhs, const T& rhs)
{
	return !(lhs < rhs);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace relations
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
