/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "PlanarSurface.h"

#include "GmshPlanarSurface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void PlanarSurface::construct() noexcept
{
	std::size_t returnTag;

	if (hasHoles())
		returnTag = interface::GmshPlanarSurface {}
		(
			tag_,
			boundaryCRef(),
			holesCRef()
		);
	else
		returnTag = interface::GmshPlanarSurface {}
		(
			tag_,
			boundaryCRef()
		);

	assert(returnTag == tag_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
