/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshAddField.h"

#include "GmshControl.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshAddField::execute
(
	const std::size_t tag,
	const String& type
) const noexcept
{
	assert(GmshControl::initialized());

	try
	{
		return static_cast<std::size_t>
		(
			gmsh::model::mesh::field::add
			(
				type,
				static_cast<Integer>(tag)
			)
		);
	}
	catch(...)
	{
		return 0;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
