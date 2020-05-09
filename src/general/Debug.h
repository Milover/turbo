/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Highly advanced debugging tools and utilities.

\*---------------------------------------------------------------------------*/

#ifndef DEBUG_DEBUG_H
#define DEBUG_DEBUG_H

#include <iostream>
#include <utility>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace debug
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

template<typename... Ts>
inline void echo(Ts&&... ts)
{
    (std::cerr << ... << std::forward<Ts>(ts)) << '\n';
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace debug
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
