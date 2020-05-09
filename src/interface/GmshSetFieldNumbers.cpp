/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshSetFieldNumbers.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshSetFieldNumbers::execute
(
	const std::size_t tag,
	const String& variable,
	const Floatvector& values
) const noexcept
{
	assert(GmshControl::initialized());

	gmsh::model::mesh::field::setNumbers
	(
		static_cast<Integer>(tag),
		variable,
		values
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
