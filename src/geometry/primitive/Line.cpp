/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "gmsh.h"

#include "Line.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
