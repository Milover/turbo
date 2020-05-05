/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Curve.h"

#include "General.h"
#include "PlaceholderCurve.h"
#include "Point.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Curve::Curve(const detail::PlaceholderCurve& c)
:
	ShapeBase {c.tag}
{
	auto points {c.boundary()};

	if (points.front().second)
		start_ = points.front().second;
	else
		start_.reset
		(
			new Point {points.front().first}
		);

	if (points.back().second)
		end_ = points.back().second;
	else
		end_.reset
		(
			new Point {points.back().first}
		);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Sptr<Point> Curve::endPtr() const noexcept
{
	return end_;
}


const Point& Curve::endRef() const noexcept
{
	return *end_;
}


Sptr<Point> Curve::startPtr() const noexcept
{
	return start_;
}


const Point& Curve::startRef() const noexcept
{
	return *start_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
