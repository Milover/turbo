/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "FilledSurface.h"

#include "GmshFilledSurface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void FilledSurface::construct() noexcept
{
	std::size_t returnTag;

	returnTag = interface::GmshFilledSurface {}
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
