/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <vector>

#include "gmsh.h"

#include "SurfaceFilling.h"

#include "General.h"
#include "Surface.h"
#include "Wire.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Integer SurfaceFilling::construct
(
	Wire&& wire,
	const Surface::Pointvector& points
) const noexcept
{
	std::vector<Integer> tags;

	for (auto& p : points)
		tags.push_back
		(
			p.dimTag().second
		);

	return gmsh::model::occ::addSurfaceFilling
	(
		wire.dimTag().second,
		-1,		// don't assign tag
		tags
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SurfaceFilling::SurfaceFilling
(
	Wire&& wire,
	const Surface::Pointvector& points
) noexcept
:
	Surface
	{
		construct
		(
			std::move(wire),
			points
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
