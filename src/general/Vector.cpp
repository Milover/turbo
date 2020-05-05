/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <array>
#include <cmath>
#include <numeric>
#include <utility>

#include "Vector.h"

#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

constexpr Vector::Vector
(
	const Float x,
	const Float y,
	const Float z
) noexcept
:
	data_ {x, y, z}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Vector::Iterator Vector::begin() noexcept
{
	return data_.begin();
}


Vector::Constiterator Vector::begin() const noexcept
{
	return data_.begin();
}


Vector::Iterator Vector::end() noexcept
{
	return data_.end();
}


Vector::Constiterator Vector::end() const noexcept
{
	return data_.end();
}


constexpr Vector Vector::origin() noexcept
{
	return Vector {0.0, 0.0, 0.0};
}


Float& Vector::x() noexcept
{
	return data_[0];
}


Float& Vector::x() const noexcept
{
	return data_[0];
}


constexpr Vector Vector::xAxis() noexcept
{
	return Vector {1.0, 0.0, 0.0};
}


Float& Vector::y() noexcept
{
	return data_[1];
}


const Float& Vector::y() const noexcept
{
	return data_[1];
}


constexpr Vector Vector::yAxis() noexcept
{
	return Vector {0.0, 1.0, 0.0};
}


Float& Vector::z() noexcept
{
	return data_[2];
}


const Float& Vector::z() const noexcept
{
	return data_[2];
}


constexpr Vector Vector::zAxis() noexcept
{
	return Vector {0.0, 0.0, 1.0};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Float& operator[](const Sizetype& i) noexcept
{
	return data_[i];
}


const Float& operator[](const Sizetype& i) const noexcept
{
	return data_[i];
}


Vector& operator+=(const Vector& v) noexcept
{
	data_[0] += v.data_[0];
	data_[1] += v.data_[1];
	data_[2] += v.data_[2];

	return *this;
}


Vector& operator-=(const Vector& v) noexcept
{
	data_[0] -= v.data_[0];
	data_[1] -= v.data_[1];
	data_[2] -= v.data_[2];

	return *this;
}


Vector& operator*=(const Float f) noexcept
{
	data_[0] *= f;
	data_[1] *= f;
	data_[2] *= f;

	return *this;
}


Vector& operator/=(const Float f) noexcept
{
	data_[0] /= f;
	data_[1] /= f;
	data_[2] /= f;

	return *this;
}


bool operator==(const Vector& v) const noexcept
{
	return isEqual(data_[0], v.data_[0])
		&& isEqual(data_[1], v.data_[1])
		&& isEqual(data_[2], v.data_[2]);
}


// * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * * //

Vector operator+(Vector lhs, const Vector& rhs) noexcept
{
	lhs += rhs;
	return lhs;
}


Vector operator+(Vector v) noexcept
{
	return v;
}


Vector operator-(Vector lhs, const Vector& rhs) noexcept
{
	lhs -= rhs;
	return lhs;
}


Vector operator-(Vector v) noexcept
{
	v *= -1.0;
	return v;
}


Vector operator*(Vector lhs, const Float& rhs) noexcept
{
	lhs *= rhs;
	return lhs;
}


Vector operator/(Vector lhs, const Float& rhs) noexcept
{
	lhs /= rhs;
	return lhs;
}


bool operator!=(const Vector& lhs, const Vector& rhs) noexcept
{
	return !(lhs == rhs);
}



// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

Float angleBetween(const Vector& v1, const Vector& v2) noexcept
{
	return std::acos
	(
		dot(v1, v2) / (mag(v1) * mag(v2))
	);
}


Vector cross(const Vector& v1, const Vector& v2) noexcept
{
	return Vector
	{
		v1.y() * v2.z() - v1.z() * v2.y(),
		v1.z() * v2.x() - v1.x() * v2.z(),
		v1.x() * v2.y() - v1.y() * v2.x()
	};
}


Float dot(const Vector& v1, const Vector& v2) noexcept
{
	return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}


bool isNan(const Vector& v) noexcept
{
	return std::isnan(v.x())
		&& std::isnan(v.y())
		&& std::isnan(v.z());
}


Float mag(const Vector& v) noexcept
{
	return std::hypot
	(
		v.x(), v.y(), v.z()
	);
}


Vector midpoint(const Vector& v1, const Vector& v2) noexcept
{
	return Vector
	{
		(v1 + v2) * 0.5
	};
}


Vector unit(Vector v) noexcept
{
	v /= mag(v);
	return v;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
