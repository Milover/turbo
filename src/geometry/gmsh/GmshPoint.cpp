/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshPoint.h"

#include "GmshControl.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshPoint::operator()
(
	const std::size_t tag,
	const Vector& coords
) const noexcept
{
	assert(GmshControl::initialized());

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addPoint
		(
			coords.x(),
			coords.y(),
			coords.z(),
			0.0,			// mesh size
			static_cast<Integer>(tag)
		)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
