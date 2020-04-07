/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <vector>

#include "gmsh.h"

#include "Curve.h"
#include "Point.h"
#include "Spline.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

int Spline::construct
(
	Point start,
	Point end,
	const Spline::Pointvector& points
) const noexcept
{
	std::vector<int> tags;

	for (const auto& p : points)
	{
		if (&p == &points.front())
			tags.push_back
			(
				start.getDimTag().second
			);
		else if (&p == &points.back())
			tags.push_back
			(
				end.getDimTag().second
			);
		else
			tags.push_back
			(
				p.getDimTag().second
			);
	}

	return gmsh::model::occ::addSpline(tags);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Spline::Spline(const Spline::Pointvector& points) noexcept
:
	Curve
	{
		construct
		(
			points.front(),
			points.back(),
			points
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
