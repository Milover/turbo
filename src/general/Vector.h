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

#include "General.h"
#include "Utility.h"

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
		) noexcept
		:
			data_ {x, y, z}
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

		//- Return origin point
		inline static constexpr Vector origin()
		{
			return Vector {0.0, 0.0, 0.0};
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

		//- Return unit x-axis vector
		inline static constexpr Vector xAxis()
		{
			return Vector {1.0, 0.0, 0.0};
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

		//- Return unit y-axis vector
		inline static constexpr Vector yAxis()
		{
			return Vector {0.0, 1.0, 0.0};
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

		//- Return unit z-axis vector
		inline static constexpr Vector zAxis()
		{
			return Vector {0.0, 0.0, 1.0};
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

			return *this;
		}

		//- Subtraction assignment operator
		inline Vector& operator-=(const Vector& v) noexcept
		{
			data_[0] -= v.data_[0];
			data_[1] -= v.data_[1];
			data_[2] -= v.data_[2];

			return *this;
		}

		//- Scalar multiplication assignment operator
		inline Vector& operator*=(const Float f) noexcept
		{
			data_[0] *= f;
			data_[1] *= f;
			data_[2] *= f;

			return *this;
		}

		//- Scalar division assignment operator
		inline Vector& operator/=(const Float f) noexcept
		{
			data_[0] /= f;
			data_[1] /= f;
			data_[2] /= f;

			return *this;
		}

		//- Equality operator
		inline bool operator==(const Vector& v) const noexcept
		{
			return isEqual(data_[0], v.data_[0])
				&& isEqual(data_[1], v.data_[1])
				&& isEqual(data_[2], v.data_[2]);
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
inline bool operator!=(const Vector& lhs, const Vector& rhs) noexcept
{
	return !(lhs == rhs);
}


// * * * * * * * * * * * * * * Global Operations * * * * * * * * * * * * * * //

// Magnitude
inline Float mag(const Vector& v) noexcept
{
	return std::hypot
	(
		v.x(), v.y(), v.z()
	);
}


// Normalize (to unit vector)
inline Vector unit(Vector v)
{
	v /= mag(v);
	return v;
}


// Dot product
inline Float dot(const Vector& v1, const Vector& v2)
{
	return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}


// Cross product
inline Vector cross(const Vector& v1, const Vector& v2) noexcept
{
	return Vector
	{
		v1.y() * v2.z() - v1.z() * v2.y(),
		v1.z() * v2.x() - v1.x() * v2.z(),
		v1.x() * v2.y() - v1.y() * v2.x()
	};
}


// Midpoint
inline Vector midpoint(const Vector& v1, const Vector& v2) noexcept
{
	return Vector
	{
		(v1 + v2) * 0.5
	};
}


// Is NAN
inline bool isNan(const Vector& v) noexcept
{
	return std::isnan(v.x())
		&& std::isnan(v.y())
		&& std::isnan(v.z());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
