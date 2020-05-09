/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshPlanarSurface.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshPlanarSurface::operator()
(
	const std::size_t tag,
	const Curvevector& boundary,
	const std::vector<Curvevector>& holes
) const noexcept
{
	assert(GmshControl::initialized());

	// create wires
	auto makeWire = [](const Curvevector& curves)
	{
		std::vector<Integer> tags;
		tags.reserve(curves.size());

		for (auto& c : curves)
			tags.push_back
			(
				static_cast<Integer>(c->tag())
			);

		return gmsh::model::occ::addWire(tags);
	};

	std::vector<Integer> wires;
	wires.reserve(holes.size() + 1);

	wires.push_back(makeWire(boundary));
	for (auto& h : holes)
		wires.push_back(makeWire(h));

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addPlaneSurface(wires, tag)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
