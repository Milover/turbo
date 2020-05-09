/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshLine

Description
	GmshLine class

SourceFiles
	GmshLine.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_LINE_H
#define INTERFACE_GMSH_LINE_H

#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshLine Definition
\*---------------------------------------------------------------------------*/

struct GmshLine
{
	//- Create a line and return it's tag
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const geometry::Point& start,
		const geometry::Point& end
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
