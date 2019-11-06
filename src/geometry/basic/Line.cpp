/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "gmsh.h"

#include "Axis.h"
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
) const noexcept
{
	return gmsh::model::geo::addLine
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
) noexcept
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


Line::Line(const Line& line) noexcept
:
	Shape {line}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Line::~Line()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Line::getLength() const noexcept
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
