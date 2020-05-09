/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshRecombine.h"

#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshRecombine::operator()(const geometry::Surface* surface) const noexcept
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	gmsh::model::mesh::setRecombine
	(
		surface->dim,
		static_cast<Integer>(surface->tag())
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
