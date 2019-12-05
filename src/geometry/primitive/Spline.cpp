/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <initializer_list>
#include <utility>
#include <vector>

#include "gmsh.h"

#include "Point.h"
#include "Shape.h"
#include "Spline.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int Spline::construct(const Spline::Pointvector& points) const noexcept
{
	std::vector<int> tags;

	for (const auto& p : points)
		tags.push_back
		(
			p.getDimTag().second
		);

	return gmsh::model::geo::addSpline(tags);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Spline::Spline(std::initializer_list<Point> points) noexcept
:
	Shape
	{
		std::pair<int, int>
		{
			1,		// dimension
			construct
			(
				Spline::Pointvector {points}
			)
		}
	}
{}


Spline::Spline(const Spline::Pointvector points) noexcept
:
	Shape
	{
		std::pair<int, int>
		{
			1,		// dimension
			construct(points)
		}
	}
{}


Spline::Spline(const Spline& spline) noexcept
:
	Shape {spline}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
