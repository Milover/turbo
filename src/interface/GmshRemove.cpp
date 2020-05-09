/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshRemove.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void GmshRemove::execute
(
	const std::size_t tag,
	const Integer dimension
) const noexcept
{
	assert(GmshControl::initialized());

	gmsh::model::occ::remove
	(
		Vectorpair<Integer>
		{
			{dimension, static_cast<Integer>(tag)}
		},
		false		// non-recursive
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
