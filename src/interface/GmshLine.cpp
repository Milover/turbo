/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshLine.h"

#include "General.h"
#include "GmshControl.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshLine::operator()
(
	const std::size_t tag,
	const geometry::Point& start,
	const geometry::Point& end
) const noexcept
{
	assert(GmshControl::initialized());

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addLine
		(
			static_cast<Integer>(start.tag()),
			static_cast<Integer>(end.tag()),
			static_cast<Integer>(tag)
		)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
