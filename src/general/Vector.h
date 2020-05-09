/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Vector

Description
	Vector class

SourceFiles
	Vector.cpp

\*---------------------------------------------------------------------------*/

#ifndef VECTOR_H
#define VECTOR_H

#include <array>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class Vector Declaration
\*---------------------------------------------------------------------------*/

class Vector
{
private:

	using Array = std::array<Float, 3>;
	using Sizetype = std::array<Float, 3>::size_type;
	using Iterator = Array::iterator;
	using Constiterator = Array::const_iterator;


	// Private data
		
		Array data_;


public:

	// Constructors

		//- Default constructor
		Vector() = default;
		
		//- Construct from components
		constexpr Vector
		(
			const Float x,
			const Float y,
			const Float z = 0.0
		) noexcept;


	// Member functions

		//- Get iterator to beginning
		Iterator begin() noexcept;

		//- Get const iterator to beginning
		Constiterator begin() const noexcept;

		//- Get iterator to end
		Iterator end() noexcept;

		//- Get const iterator to end
		Constiterator end() const noexcept;

		//- Return origin point
		static constexpr Vector origin() noexcept;

		//- Access X component by reference
		Float& x() noexcept;

		//- Access X component by const reference
		const Float& x() const noexcept;

		//- Return unit x-axis vector
		static constexpr Vector xAxis() noexcept;

		//- Access Y component by reference
		Float& y() noexcept;

		//- Access Y component by const reference
		const Float& y() const noexcept;

		//- Return unit y-axis vector
		static constexpr Vector yAxis() noexcept;

		//- Access Z component by reference
		Float& z() noexcept;

		//- Access Z component by const reference
		const Float& z() const noexcept;

		//- Return unit z-axis vector
		static constexpr Vector zAxis() noexcept;


	// Member operators

		//- Access operator
		Float& operator[](const Sizetype& i) noexcept;

		//- Access operator
		const Float& operator[](const Sizetype& i) const noexcept;

		//- Addition assignment operator
		Vector& operator+=(const Vector& v) noexcept;

		//- Subtraction assignment operator
		Vector& operator-=(const Vector& v) noexcept;

		//- Scalar multiplication assignment operator
		Vector& operator*=(const Float f) noexcept;

		//- Scalar division assignment operator
		Vector& operator/=(const Float f) noexcept;

		//- Equality operator
		bool operator==(const Vector& v) const noexcept;

};


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

constexpr Vector Vector::origin() noexcept
{
	return Vector {0.0, 0.0, 0.0};
}


constexpr Vector Vector::xAxis() noexcept
{
	return Vector {1.0, 0.0, 0.0};
}


constexpr Vector Vector::yAxis() noexcept
{
	return Vector {0.0, 1.0, 0.0};
}


constexpr Vector Vector::zAxis() noexcept
{
	return Vector {0.0, 0.0, 1.0};
}


// * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * * //

//- Addition
Vector operator+(Vector lhs, const Vector& rhs) noexcept;


//- Unary plus
Vector operator+(Vector v) noexcept;


//- Subtraction
Vector operator-(Vector lhs, const Vector& rhs) noexcept;


//- Unary minus
Vector operator-(Vector v) noexcept;


//- Multiplication by scalar
Vector operator*(Vector lhs, const Float& rhs) noexcept;


//- Division by scalar
Vector operator/(Vector lhs, const Float& rhs) noexcept;


//- Inequality operator
bool operator!=(const Vector& lhs, const Vector& rhs) noexcept;


// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

// Angle between two vectors
Float angleBetween(const Vector& v1, const Vector& v2) noexcept;


// Cross product
Vector cross(const Vector& v1, const Vector& v2) noexcept;


// Dot product
Float dot(const Vector& v1, const Vector& v2) noexcept;


// Is NAN
bool isNan(const Vector& v) noexcept;


// Magnitude
Float mag(const Vector& v) noexcept;


// Midpoint
Vector midpoint(const Vector& v1, const Vector& v2) noexcept;


// Normalize (to unit vector)
Vector unit(Vector v) noexcept;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
