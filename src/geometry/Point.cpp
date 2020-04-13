/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "gmsh.h"

#include "Point.h"

#include "General.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Integer Point::construct
(
	const Float x,
	const Float y,
	const Float z
) const noexcept
{
	return gmsh::model::occ::addPoint(x, y, z);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Point::Point
(
	const Float x,
	const Float y,
	const Float z
) noexcept
:
	Shape
	{
		std::make_pair
		(
			0,		// dimension
			construct(x, y, z)
		)
	}
{}


Point::Point(const Point::Coordinates& c) noexcept
:
	Point
	{
		c.x(), c.y(), c.z()
	}
{}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Point::Coordinates Point::coordinates() const noexcept
{
	return boundingBox().first;
}


Point Point::origin()
{
	return Point {0, 0};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
