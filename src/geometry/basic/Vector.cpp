/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <stdexcept>

#include "Axis.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Vector::Vector() noexcept
:
	x {0.0},
	y {0.0},
	z {0.0}
{}


Vector::Vector
(
	const double x,
	const double y,
	const double z
) noexcept
:
	x {x},
	y {y},
	z {z}
{}


Vector::Vector(const Axis& axis) noexcept
:
	x {0.0},
	y {0.0},
	z {0.0}
{
	switch(axis)
	{
		case Axis::X :
			x = 1.0;
			break;
		case Axis::Y :
			y = 1.0;
			break;
		case Axis::Z :
			z = 1.0;
			break;
	}

}


Vector::Vector(const Vector& vector) noexcept
:
	x {vector.x},
	y {vector.y},
	z {vector.z}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Vector::~Vector()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Vector::getMagnitude() const noexcept
{
	return std::hypot(x, y, z);
}


Vector Vector::getUnitVector() const
{
	double magnitude {getMagnitude()};

	return *this / magnitude;
}


double Vector::dot(const Vector& vector) const noexcept
{
	return x * vector.x +
		   y * vector.y +
		   z * vector.z;
}


Vector Vector::ex(const Vector& vector) const noexcept
{
	return Vector
	{
		y * vector.z - z * vector.y,
	   -x * vector.z + z * vector.x,
		x * vector.y - y * vector.x
	};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Vector& Vector::operator=(const Vector& vector) noexcept
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return *this;
}


Vector Vector::operator+(const Vector& vector) const noexcept
{
	return Vector
	{
		x + vector.x,
		y + vector.y,
		z + vector.z
	};
}


Vector Vector::operator+() const noexcept
{
	return Vector {*this};
}


Vector& Vector::operator+=(const Vector& vector) noexcept
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}


Vector Vector::operator-(const Vector& vector) const noexcept
{
	return Vector
	{
		x - vector.x,
		y - vector.y,
		z - vector.z
	};
}


Vector Vector::operator-() const noexcept
{
	return Vector
	{
		-x,
		-y,
		-z
	};
}


Vector& Vector::operator-=(const Vector& vector) noexcept
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}


Vector Vector::operator*(const double d) const noexcept
{
	return Vector
	{
		x * d,
		y * d,
		z * d
	};
}


Vector& Vector::operator*=(const double d) noexcept
{
	x *= d;
	y *= d;
	z *= d;

	return *this;
}


Vector Vector::operator/(const double d) const
{
	if (isEqual(d, 0.0))
		throw std::invalid_argument
		(
			"turbo::geometry::Vector::operator/(const double): "
			"Divide by zero"
		);

	return Vector
	{
		x / d,
		y / d,
		z / d
	};
}


Vector& Vector::operator/=(const double d)
{
	if (isEqual(d, 0.0))
		throw std::invalid_argument
		(
			"turbo::geometry::Vector::operator/=(const double): "
			"Divide by zero"
		);

	x /= d;
	y /= d;
	z /= d;

	return *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
