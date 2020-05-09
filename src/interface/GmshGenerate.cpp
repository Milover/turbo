/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshGenerate.h"

#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshGenerate::operator()() const noexcept
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	gmsh::model::mesh::generate();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
