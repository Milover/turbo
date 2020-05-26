/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshLoft.h"

#include "Curve.h"
#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

std::vector<std::size_t> GmshLoft::operator()
(
	const Curvevector& curves
) const noexcept
{
	assert(GmshControl::initialized());

	// because we're about to create free floating geometry
	GmshBase::unsynchronize();

	Intvector wires;
	wires.reserve(curves.size());

	Intvector tmp {};
	tmp.emplace_back();
	for (auto& c : curves)
	{
		tmp.front() = static_cast<Integer>(c->tag());

		wires.emplace_back
		(
			gmsh::model::occ::addWire(tmp)
		);
	}

	Vectorpair<Integer> dimTags;

	gmsh::model::occ::addThruSections
	(
		wires,
		dimTags,
		-1,			// don't prescribe tag
		false,		// don't make solid
		false		// don't make ruled
	);

	std::vector<std::size_t> tags;
	tags.reserve(dimTags.size());

	for (auto [d, t] : dimTags)
		tags.emplace_back
		(
			static_cast<std::size_t>(t)
		);

	return tags;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
