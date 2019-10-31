/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <stdexcept>

#include "Axis.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Vector::Vector()
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
)
:
	x {x},
	y {y},
	z {z}
{}


Vector::Vector(const Vector& vector)
:
	x {vector.x},
	y {vector.y},
	z {vector.z}
{}


Vector::Vector(const Axis& axis)
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


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Vector::~Vector()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Vector::getMagnitude() const
{
	return std::hypot(x, y, z);
}


Vector Vector::getUnitVector() const noexcept(false)
{
	double magnitude {getMagnitude()};

	if (magnitude == 0)
		throw std::domain_error
		(
			"Vector::getUnitVector(): Divide by zero"
		);

	return Vector
	{
		x / magnitude,
		y / magnitude,
		z / magnitude
	};
}


double Vector::dot(const Vector& vector) const
{
	return x * vector.x +
		   y * vector.y +
		   z * vector.z;
}


Vector Vector::ex(const Vector& vector) const
{
	return Vector
	{
		y * vector.z - z * vector.y,
	   -x * vector.z + z * vector.x,
		x * vector.y - y * vector.x
	};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Vector& Vector::operator=(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return *this;
}


Vector Vector::operator+(const Vector& vector) const
{
	return Vector
	{
		x + vector.x,
		y + vector.y,
		z + vector.z
	};
}


Vector Vector::operator+() const
{
	return Vector {*this};
}


Vector Vector::operator-(const Vector& vector) const
{
	return Vector
	{
		x - vector.x,
		y - vector.y,
		z - vector.z
	};
}


Vector Vector::operator-() const
{
	return Vector
	{
		-x,
		-y,
		-z
	};
}


Vector Vector::operator*(const double d) const
{
	return Vector
	{
		x * d,
		y * d,
		z * d
	};
}


Vector Vector::operator/(const double d) const noexcept(false)
{
	if (d == 0)
		throw std::invalid_argument
		(
			"Vector::operator/(const double): Divide by zero"
		);

	return Vector
	{
		x / d,
		y / d,
		z / d
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
