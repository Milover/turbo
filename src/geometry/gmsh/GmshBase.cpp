/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshBase.h"

#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

GmshBase::GmshBase() noexcept
{
	GmshBase::sync_ = false;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool GmshBase::sync() noexcept
{
	return GmshBase::sync_;
}


void GmshBase::synchronize() noexcept
{
	assert(GmshControl::initialized());

	if (!GmshBase::sync())
	{
		gmsh::model::occ::synchronize();
		GmshBase::sync_ = true;
	}
}


void GmshBase::unsynchronize() noexcept
{
	GmshBase::sync_ = false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
