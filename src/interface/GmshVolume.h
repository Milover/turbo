/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshVolume

Description
	GmshVolume class

SourceFiles
	GmshVolume.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_VOLUME_H
#define INTERFACE_GMSH_VOLUME_H

#include <vector>

#include "Surface.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshVolume Declaration
\*---------------------------------------------------------------------------*/

struct GmshVolume
{
	using Surfacevector = Sptrvector<geometry::Surface>;

	//- Create a volume from vectors of surfaces forming a closed loops.
	//	The first vector defines the outer boundary of the volume
	//	while the rest define hole boundaries within the volume (if any).
	//	NOTE: no check is made whether the surface loop is closed
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const Surfacevector& boundary,
		const std::vector<Surfacevector>& holes = std::vector<Surfacevector> {}
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
