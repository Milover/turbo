/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshWrite.h"

#include "Error.h"
#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshWrite::operator()(const String& filename) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	try
	{
		gmsh::write(filename);
	}
	catch(...)
	{
		error(FUNC_INFO, "output error");
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
