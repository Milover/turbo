/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshRecombine

Description
	GmshRecombine class

SourceFiles
	GmshRecombine.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_RECOMBINE_H
#define GEOMETRY_INTERFACE_GMSH_RECOMBINE_H

#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshRecombine Definition
\*---------------------------------------------------------------------------*/

struct GmshRecombine
{
	//- Create a point
	void operator()(const Surface* surface) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
