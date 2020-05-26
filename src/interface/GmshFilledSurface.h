/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshFilledSurface

Description
	GmshFilledSurface class

SourceFiles
	GmshFilledSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_FILLED_SURFACE_H
#define INTERFACE_GMSH_FILLED_SURFACE_H

#include <vector>

#include "Curve.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
					Class GmshFilledSurface Declaration
\*---------------------------------------------------------------------------*/

struct GmshFilledSurface
{
	using Curvevector = Sptrvector<geometry::Curve>;

	//- Create a surface from a vector of curves
	//	NOTE: no check is made whether the loop is closed
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const Curvevector& boundary
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
