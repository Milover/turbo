/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshVolume.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshVolume::operator()
(
	const std::size_t tag,
	const Surfacevector& boundary,
	const std::vector<Surfacevector>& holes
) const noexcept
{
	assert(GmshControl::initialized());

	// create shells
	auto makeShell = [](const Surfacevector& surfaces)
	{
		Intvector tags;
		tags.reserve(surfaces.size());

		for (auto& s : surfaces)
			tags.emplace_back
			(
				static_cast<Integer>(s->tag())
			);

		return gmsh::model::occ::addSurfaceLoop
		(
			tags,
			-1,			// don't prescribe tag
			true		// sewing on
		);
	};

	Intvector shells;
	shells.reserve(holes.size() + 1);

	shells.emplace_back(makeShell(boundary));
	for (auto& h : holes)
		shells.emplace_back(makeShell(h));

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addVolume(shells, tag)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
