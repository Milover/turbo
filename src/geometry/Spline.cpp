/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "gmsh.h"

#include "Spline.h"

#include "Curve.h"
#include "General.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Integer Spline::construct
(
	Point start,
	Point end,
	const Spline::Pointvector& points
) const noexcept
{
	std::vector<Integer> tags;

	for (const auto& p : points)
	{
		if (&p == &points.front())
			tags.push_back
			(
				start.dimTag().second
			);
		else if (&p == &points.back())
			tags.push_back
			(
				end.dimTag().second
			);
		else
			tags.push_back
			(
				p.dimTag().second
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
