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
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshSmooth::operator()
(
	const geometry::Surface* surface,
	Integer numIter
) const noexcept
{
	assert(GmshControl::initialized());

	if (numIter < 0)
		numIter = 0;

	gmsh::model::mesh::setSmoothing
	(
		surface->dim,
		static_cast<Integer>(surface->tag()),
		numIter
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
