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

#include "Axis.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// Forward declarations

/*---------------------------------------------------------------------------*\
						Class Vector Declaration
\*---------------------------------------------------------------------------*/

struct Vector
{
	// Public data
		
		double x;
		double y;
		double z;

	// Constructors
		
		//- Default constructor
		Vector() noexcept;

		//- Construct from components
		Vector
		(
			const double x,
			const double y,
			const double z = 0
		) noexcept;

		//- Construct from an axis
		Vector(const Axis&) noexcept;

		//- Copy constructor
		Vector(const Vector&) noexcept;


	//- Destructor
	virtual ~Vector();


	// Member functions
	
		//- Get Vector intensity
		double getMagnitude() const noexcept;

		//- Get unit vector
		Vector getUnitVector() const;

		//- Dot product
		double dot(const Vector&) const noexcept;

		//- Cross product
		Vector ex(const Vector&) const noexcept;


	// Member operators
		
		//- Assignment operator
		Vector& operator=(const Vector&) noexcept;

		//- Addition operator
		Vector operator+(const Vector&) const noexcept;

		//- Unary plus operator
		Vector operator+() const noexcept;

		//- Addition assignment operator
		Vector& operator+=(const Vector&) noexcept;

		//- Subtraction operator
		Vector operator-(const Vector&) const noexcept;

		//- Unary minus operator
		Vector operator-() const noexcept;

		//- Subtraction assignment operator
		Vector& operator-=(const Vector&) noexcept;

		//- Scalar multiplication
		Vector operator*(const double) const noexcept;

		//- Scalar multiplication assignment operator
		Vector& operator*=(const double) noexcept;

		//- Scalar division
		Vector operator/(const double) const;

		//- Scalar multiplication assignment operator
		Vector& operator/=(const double) noexcept;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
