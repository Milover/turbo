/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <vector>

#include "gmsh.h"

#include "SurfaceSection.h"

#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Integer SurfaceSection::construct(Surface::Wirevector&& wires) const noexcept
{
	std::vector<Integer> tags;
	Vectorpair<Integer> outDimTags;

	for (auto& w : wires)
		tags.push_back
		(
			w.dimTag().second
		);

	gmsh::model::occ::addThruSections
	(
		tags,
		outDimTags,
		-1,			// don't assign tag
		false,		// don't make solid
		false		// don't make ruled
	);

	return outDimTags.front().second;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SurfaceSection::SurfaceSection(Surface::Wirevector&& wires) noexcept
:
	Surface
	{
		construct
		(
			std::move(wires)
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
