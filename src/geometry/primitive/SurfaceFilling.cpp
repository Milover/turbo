/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <vector>

#include "gmsh.h"

#include "Surface.h"
#include "SurfaceFilling.h"
#include "Utility.h"
#include "Wire.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int SurfaceFilling::construct
(
	Wire&& wire,
	const Surface::Pointvector& points
) const noexcept
{
	std::vector<int> tags;

	for (auto& p : points)
		tags.push_back
		(
			p.getDimTag().second
		);

	return gmsh::model::occ::addSurfaceFilling
	(
		wire.getDimTag().second,
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
