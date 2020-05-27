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
#include <cmath>
#include <ostream>

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


	// Member functions

		//- Rotate around an axis by 'angle' radians
		//	perm = 0 == x-axis
		//	perm = 1 == z-axis
		//	perm = 2 == y-axis
		template<std::size_t permutation>
		void rotate(const Float angle) noexcept;


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

		//- Rotate around x-axis by 'angle' radians
		void rotateX(const Float angle) noexcept;

		//- Rotate around y-axis by 'angle' radians
		void rotateY(const Float angle) noexcept;

		//- Rotate around z-axis by 'angle' radians
		void rotateZ(const Float angle) noexcept;

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


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<std::size_t permutation>
void Vector::rotate(const Float angle) noexcept
{
	static_assert(permutation >= 0 && permutation <= 2);

	static constexpr std::size_t indices[3]
	{
		(0 + permutation) % 3,
		(1 + permutation) % 3,
		(2 + permutation) % 3
	};

	Float c {std::cos(angle)};
	Float s {std::sin(angle)};

	Float f = data_[indices[1]];
	Float g = data_[indices[2]];

	data_[indices[1]] = f * c - g * s;
	data_[indices[2]] = f * s + g * c;
}


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
Vector operator*(Vector lhs, const Float rhs) noexcept;


//- Multiplication by scalar
Vector operator*(const Float lhs, Vector rhs) noexcept;


//- Division by scalar
Vector operator/(Vector lhs, const Float rhs) noexcept;


//- Division by scalar
Vector operator/(const Float lhs, Vector rhs) noexcept;


//- Inequality operator
bool operator!=(const Vector& lhs, const Vector& rhs) noexcept;

//- Stream output operator, formatted output '(x, y, z)'
std::ostream& operator<<(std::ostream& os, const Vector& v);


// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

//- Angle between two vectors
Float angleBetween(const Vector& v1, const Vector& v2) noexcept;


//- Cross product
Vector cross(const Vector& v1, const Vector& v2) noexcept;


//- Dot product
Float dot(const Vector& v1, const Vector& v2) noexcept;


//- Is NAN
bool isNan(const Vector& v) noexcept;


//- Magnitude
Float mag(const Vector& v) noexcept;


//- Midpoint
Vector midpoint(const Vector& v1, const Vector& v2) noexcept;


//- Rotate around x-axis by 'angle' radians
Vector rotateX(Vector v, const Float angle) noexcept;


//- Rotate around y-axis by 'angle' radians
Vector rotateY(Vector v, const Float angle) noexcept;


//- Rotate around z-axis by 'angle' radians
Vector rotateZ(Vector v, const Float angle) noexcept;


//- Normalize (to unit vector)
Vector unit(Vector v) noexcept;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
