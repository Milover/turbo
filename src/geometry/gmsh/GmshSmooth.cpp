/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshSmooth.h"

#include "General.h"
#include "GmshControl.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshSmooth::operator()
(
	const Surface* surface,
	const Integer numIter
) const noexcept;
{
	assert(GmshControl::initialized());

	if (numIter < 0)
		numIter = 0;

	gmsh::model::mesh::setRecombine
	(
		surface->dim,
		static_cast<Integer>(surface->tag()),
		numIter
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
