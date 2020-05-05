/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshBezier

Description
	GmshBezier class

SourceFiles
	GmshBezier.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_BEZIER_H
#define GEOMETRY_INTERFACE_GMSH_BEZIER_H

#include <vector>

#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
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
		const Point& start,
		const std::vector<Point>& points,
		const Point& end
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
