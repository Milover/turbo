/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshSetBLMesh.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void GmshSetBLMesh::execute(const std::size_t tag) const noexcept
{
	assert(GmshControl::initialized());

	gmsh::model::mesh::field::setAsBoundaryLayer(static_cast<Integer>(tag));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
