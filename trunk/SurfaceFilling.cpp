/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

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
	const Pointvector& points
) const noexcept
{
	Intvector tags;

	for (auto& p : points)
		tags.push_back(p.tag());

	return gmsh::model::occ::addSurfaceFilling
	(
		wire.tag()
		-1,		// don't assign tag
		tags
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

SurfaceFilling::SurfaceFilling
(
	Wire&& wire,
	const Pointvector& points
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
