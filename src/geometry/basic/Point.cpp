/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "gmsh.h"

#include "Axis.h"
#include "Point.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int Point::construct
(
	const double x,
	const double y,
	const double z
) const noexcept
{
	return gmsh::model::geo::addPoint(x, y, z);
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


Point::Point(const Point& point) noexcept
:
	Shape {point}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Point::~Point()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::vector<double> Point::getCoordinates() const noexcept
{
	Vectorpair<double> minMax {getBoundingBox()};
	
	return std::vector<double>
	{
		minMax[toUnderlying(Axis::X)].first,
		minMax[toUnderlying(Axis::Y)].first,
		minMax[toUnderlying(Axis::Z)].first
	};

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
