/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshRecombine

Description
	GmshRecombine class

SourceFiles
	GmshRecombine.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_RECOMBINE_H
#define INTERFACE_GMSH_RECOMBINE_H

#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshRecombine Definition
\*---------------------------------------------------------------------------*/

struct GmshRecombine
{
	//- Create a point
	//	NOTE: calls GmshBase::synchronize()
	void operator()(const geometry::Surface* surface) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
