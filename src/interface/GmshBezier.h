/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshBezier

Description
	GmshBezier class

SourceFiles
	GmshBezier.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_BEZIER_H
#define INTERFACE_GMSH_BEZIER_H

#include <vector>

#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshBezier Definition
\*---------------------------------------------------------------------------*/

struct GmshBezier
{
	//- Create a bezier spline and return it's tag
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const geometry::Point& start,
		const std::vector<geometry::Point>& points,
		const geometry::Point& end
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
