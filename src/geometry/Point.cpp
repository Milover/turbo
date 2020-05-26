/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "Point.h"

#include "General.h"
#include "GmshPoint.h"
#include "PlaceholderPoint.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Point::construct() const noexcept
{
	auto tag
	{
		interface::GmshPoint {}
		(
			tag_,
			coords_
		)
	};

	assert(tag == tag_);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Point::Point
(
	const Float x,
	const Float y,
	const Float z
) noexcept
:
	Point {Coordinates {x, y, z}}
{}


Point::Point(const detail::PlaceholderPoint& p) noexcept
:
	ShapeBase {p.tag}
{
	coords_ = p.coordinates();
}


Point::Point(const Coordinates& c) noexcept
:
	coords_ {c}
{
	construct();
}


Point::Point(Coordinates&& c) noexcept
:
	coords_ {std::move(c)}
{
	construct();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Point::~Point() noexcept
{
	remove();
}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Point::Coordinates Point::coordinates() const noexcept
{
	return coords_;
}


Point Point::origin() noexcept
{
	return Point {Coordinates::origin()};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
