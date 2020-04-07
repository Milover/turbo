/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "gmsh.h"

#include "Axis.h"
#include "Point.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int Point::construct
(
	const double x,
	const double y,
	const double z
) const noexcept
{
	return gmsh::model::occ::addPoint(x, y, z);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Point::Point
(
	const double x,
	const double y,
	const double z
) noexcept
:
	Shape
	{
		std::pair<int, int>
		{
			0,		// dimension
			construct(x, y, z)
		}
	}
{}


Point::Point(const PointCoordinates& coordinates) noexcept
:
	Point
	{
		coordinates[Axis::X],
		coordinates[Axis::Y],
		coordinates[Axis::Z]
	}
{}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

PointCoordinates Point::getCoordinates() const noexcept
{
	Vectorpair<double> v {getBoundingBox()};

	return PointCoordinates
	{
		v[Axis::X].first,
		v[Axis::Y].first,
		v[Axis::Z].first
	};
}


Point Point::origin()
{
	return Point {0, 0};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
