/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshPlanarSurface

Description
	GmshPlanarSurface class

SourceFiles
	GmshPlanarSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_PLANAR_SURFACE_H
#define GEOMETRY_INTERFACE_GMSH_PLANAR_SURFACE_H

#include <vector>

#include "Curve.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
					Class GmshPlanarSurface Declaration
\*---------------------------------------------------------------------------*/

struct GmshPlanarSurface
{
	using Curvevector = Sptrvector<Curve>;

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
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
