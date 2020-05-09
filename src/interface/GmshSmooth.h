/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSmooth

Description
	GmshSmooth class

SourceFiles
	GmshSmooth.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SMOOTH_H
#define INTERFACE_GMSH_SMOOTH_H

#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
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
		const geometry::Surface* surface,
		Integer numIter
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
