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
#include <numeric>
#include <utility>

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class Vector Declaration
\*---------------------------------------------------------------------------*/

class Vector
:
	public vector::tag
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
		
		//- Construct from components
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Float, T>, int> = 0>
		>
		Vector
		(
			T&& x,
			T&& y,
			T&& z = 0.0
		) noexcept
		:
			data_
			{
				std::forward<T>(x),
				std::forward<T>(y),
				std::forward<T>(z)
			}
		{}


	// Member functions

		//- Get iterator to beginning
		inline Iterator begin()
		{
			return data_.begin();
		}

		//- Get const iterator to beginning
		inline Constiterator begin() const
		{
			return data_.begin();
		}

		//- Get iterator to end
		inline Iterator end()
		{
			return data_.end();
		}

		//- Get const iterator to end
		inline Constiterator end() const
		{
			return data_.end();
		}

		//- Access X component by value
		inline Float x() const noexcept
		{
			return data_[0];
		}

		//- Access X component by reference
		inline Float& x() noexcept
		{
			return data_[0];
		}

		//- Access X component by const reference
		inline const Float& x() const noexcept
		{
			return data_[0];
		}

		//- Access Y component by value
		inline Float y() const noexcept
		{
			return data_[1];
		}

		//- Access Y component by reference
		inline Float& y() noexcept
		{
			return data_[1];
		}

		//- Access Y component by const reference
		inline const Float& y() const noexcept
		{
			return data_[1];
		}

		//- Access Z component by value
		inline Float z() const noexcept
		{
			return data_[2];
		}

		//- Access Z component by reference
		inline Float& z() noexcept
		{
			return data_[2];
		}

		//- Access Z component by const reference
		inline const Float& z() const noexcept
		{
			return data_[2];
		}


	// Member operators

		//- Access operator
		inline Float& operator[](const Sizetype& i) noexcept
		{
			return data_[i];
		}

		//- Access operator
		inline const Float& operator[](const Sizetype& i) const noexcept
		{
			return data_[i];
		}

		//- Addition assignment operator
		inline Vector& operator+=(const Vector& v) noexcept
		{
			data_[0] += v.data_[0];
			data_[1] += v.data_[1];
			data_[2] += v.data_[2];
		}

		//- Subtraction assignment operator
		inline Vector& operator-=(const Vector& v) noexcept
		{
			data_[0] -= v.data_[0];
			data_[1] -= v.data_[1];
			data_[2] -= v.data_[2];
		}

		//- Scalar multiplication assignment operator
		inline Vector& operator*=(const Float f) noexcept
		{
			data_[0] *= f;
			data_[1] *= f;
			data_[2] *= f;
		}

		//- Scalar division assignment operator
		inline Vector& operator/=(const Float f);
		{
			if (isEqual(f, 0.0))
				THROW_ARGUMENT_ERROR("divide by 0");

			data_[0] /= f;
			data_[1] /= f;
			data_[2] /= f;
		}

		//- Equality operator
		inline bool operator==(const Vector& v) const noexcept
		{
			return data_[0] == v.data_[0]
				&& data_[1] == v.data_[1]
				&& data_[2] == v.data_[2];
		}

};


// * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * * //

//- Addition
inline Vector operator+(Vector lhs, const Vector& rhs) noexcept
{
	lhs += rhs;
	return lhs;
}


//- Unary plus
inline Vector operator+(Vector v) noexcept
{
	return v;
}


//- Subtraction
inline Vector operator-(Vector lhs, const Vector& rhs) noexcept
{
	lhs -= rhs;
	return lhs;
}


//- Unary minus
inline Vector operator-(Vector v) noexcept
{
	v *= -1.0;
	return v;
}


//- Multiplication by scalar
inline Vector operator*(Vector lhs, const Float& rhs) noexcept
{
	lhs *= rhs;
	return lhs;
}


//- Division by scalar
inline Vector operator/(Vector lhs, const Float& rhs)
{
	lhs /= rhs;
	return lhs;
}


//- Inequality operator
inline bool operator!=(const Vector& lhs, const Vector& rhs) const noexcept
{
	return !(lhs == rhs);
}


// * * * * * * * * * * * * * * Vector Operations * * * * * * * * * * * * * * //

// Magnitude
Float mag(const Vector& v) noexcept
{
	return std::hypot
	(
		v.x(), v.y(), v.z()
	);
}


// Normalize (to unit vector)
Vector unit(Vector v)
{
	v /= mag(v);
	return v;
}


// Dot product
Float dot(const Vector& v1, const Vector& v2)
{
	return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}


// Cross product
Vector cross(const Vector& v1, const Vector& v2) noexcept
{
	return Vector
	{
		v1.y() * v2.z() - v1.z() * v2.y(),
		v1.z() * v2.x() - v1.x() * v2.z(),
		v1.x() * v2.y() - v1.y() * v2.x()
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
