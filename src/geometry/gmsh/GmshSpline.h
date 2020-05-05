/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshSpline

Description
	GmshSpline class

SourceFiles
	GmshSpline.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_SPLINE_H
#define GEOMETRY_INTERFACE_GMSH_SPLINE_H

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
						Class GmshSpline Definition
\*---------------------------------------------------------------------------*/

struct GmshSpline
{
	//- Create a spline and return it's tag
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
