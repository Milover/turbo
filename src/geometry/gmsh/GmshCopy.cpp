/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshCopy.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

std::size_t GmshCopy::execute
(
	const std::size_t tag,
	const Integer dimension
) const noexcept
{
	assert(GmshControl::initialized());

	Vectorpair<Integer> dimTags;

	gmsh::model::occ::copy
	(
		Vectorpair<Integer>
		{
			{dimension, static_cast<Integer>(tag)}
		},
		dimTags
	);

	return static_cast<std::size_t>(dimTags.front().second);
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
