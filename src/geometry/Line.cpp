/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <vector>

#include "Axis.h"
#include "gmsh.h"
#include "Line.h"
#include "Point.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int Line::construct
(
	const int startTag,
	const int endTag
) const
{
	return gmsh::model::occ::addLine
	(
		startTag,
		endTag
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Line::Line
(
	Point start,
	Point end
)
:
	Shape
	{
		std::pair<int, int>
		{
			1,		// dimension
			construct
			(
				start.getDimTag().second,
				end.getDimTag().second
			)
		}
	}
{}


Line::Line(const Line& line)
:
	Shape {line}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Line::~Line()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Line::getLength() const
{
	Vectorpair<double> minMax {getBoundingBox()};

	return std::hypot
	(
		minMax[toUnderlying(Axis::X)].first - minMax[toUnderlying(Axis::X)].second,
		minMax[toUnderlying(Axis::Y)].first - minMax[toUnderlying(Axis::Y)].second,
		minMax[toUnderlying(Axis::Z)].first - minMax[toUnderlying(Axis::Z)].second
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
