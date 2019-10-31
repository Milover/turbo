/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Alias templates and some other utilities

\*---------------------------------------------------------------------------*/

#ifndef UTILITY_H
#define UTILITY_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Vector of pairs template alias
template<typename T>
using Vectorpair = std::vector<std::pair<T, T>>;


//- Static cast (enum class) to underlying type
template <typename T>
constexpr auto toUnderlying(T t) noexcept
{
	return static_cast<typename std::underlying_type_t<T>>(t);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
