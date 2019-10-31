/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>

#include "Axis.h"
#include "gmsh.h"
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
) const
{
	return gmsh::model::occ::addPoint(x, y, z);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Point::Point
(
	const double x,
	const double y,
	const double z
)
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


Point::Point(const Point& point)
:
	Shape {point}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Point::~Point()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::vector<double> Point::getCoordinates() const
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
