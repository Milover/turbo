/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Axis.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Axis::Axis
(
	double x,
	double y,
	double z,
	const Vector& vector
) noexcept
:
	point_ {x, y, z},
	vector_ {vector}
{}


Axis::Axis(const Axis& axis) noexcept
:
	point_ {axis.point_},
	vector_ {axis.vector_}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

PointCoordinates Axis::getPointCoordinates() const noexcept
{
	return point_;
}


Vector Axis::getVector() const noexcept
{
	return vector_;
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

bool Axis::operator==(const Axis& axis) const
{
	return point_ == axis.point_
		&& vector_ == axis.vector_;
}


bool Axis::operator!=(const Axis& axis) const
{
	return !(*this == axis);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
