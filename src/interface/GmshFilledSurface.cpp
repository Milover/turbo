/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshFilledSurface.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshFilledSurface::operator()
(
	const std::size_t tag,
	const Curvevector& boundary
) const noexcept
{
	assert(GmshControl::initialized());

	Intvector tmp {};
	tmp.reserve(boundary.size());

	for (auto& b : boundary)
		tmp.emplace_back
		(
			static_cast<Integer>(b->tag())
		);

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addSurfaceFilling
		(
			gmsh::model::occ::addWire(tmp),
			tag
		)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
