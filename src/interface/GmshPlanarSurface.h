/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshPlanarSurface

Description
	GmshPlanarSurface class

SourceFiles
	GmshPlanarSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_PLANAR_SURFACE_H
#define INTERFACE_GMSH_PLANAR_SURFACE_H

#include <vector>

#include "Curve.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
					Class GmshPlanarSurface Declaration
\*---------------------------------------------------------------------------*/

struct GmshPlanarSurface
{
	using Curvevector = Sptrvector<geometry::Curve>;

	//- Create a planar surface from vectors of curves
	//	forming a closed loops.
	//	The first vector defines the outer boundary of the surface
	//	while the rest define hole boundaries within the surface (if any).
	//	NOTE: no check is made whether the loop is closed
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const Curvevector& boundary,
		const std::vector<Curvevector>& holes = std::vector<Curvevector> {}
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
