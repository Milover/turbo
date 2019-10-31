/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

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
		Vector();

		//- Construct from components
		Vector
		(
			const double x,
			const double y,
			const double z = 0
		);

		//- Copy constructor
		Vector(const Vector&);
	
		//- Construct from an axis
		Vector(const Axis&);


	//- Destructor
	virtual ~Vector();


	// Member functions
	
		//- Get Vector intensity
		double getMagnitude() const;

		//- Get unit vector
		Vector getUnitVector() const noexcept(false);

		//- Dot product
		double dot(const Vector&) const;

		//- Cross product
		Vector ex(const Vector&) const;


	// Member operators
		
		//- Assignment operator
		Vector& operator=(const Vector&);

		//- Addition operator
		Vector operator+(const Vector&) const;

		//- Unary plus operator
		Vector operator+() const;

		//- Subtraction operator
		Vector operator-(const Vector&) const;

		//- Unary minus operator
		Vector operator-() const;

		//- Scalar multiplication
		Vector operator*(const double) const;

		//- Scalar division
		Vector operator/(const double) const noexcept(false);


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
