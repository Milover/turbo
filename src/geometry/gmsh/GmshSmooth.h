/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshSmooth

Description
	GmshSmooth class

SourceFiles
	GmshSmooth.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_SMOOTH_H
#define GEOMETRY_INTERFACE_GMSH_SMOOTH_H

#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshSmooth Definition
\*---------------------------------------------------------------------------*/

struct GmshSmooth
{
	//- Apply 'numIter' Laplace smoother iterations to a surface, minimum 0
	void operator()
	(
		const Surface* surface,
		const Integer numIter
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
