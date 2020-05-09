/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSpline

Description
	GmshSpline class

SourceFiles
	GmshSpline.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SPLINE_H
#define INTERFACE_GMSH_SPLINE_H

#include <vector>

#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
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
