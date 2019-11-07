/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Airfoil

Description
	Class Airfoil

SourceFiles
	Airfoil.cpp

\*---------------------------------------------------------------------------*/

#ifndef AIRFOIL_H
#define AIRFOIL_H

#include <memory>

#include "Point.h"
#include "ProfileGeneratorInterface.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Airfoil Declaration
\*---------------------------------------------------------------------------*/

class Airfoil
{
private:

	// Private data

		Vectorpair<std::unique_ptr<Point>> surfacePoints_;


public:
	
	// Constructors

		//- Construct NACA airfoil (4-digit only)
		//  from a ProfileGeneratorInterface
		Airfoil
		(
			const ProfileGeneratorInterface& generator
		);

		//- Disallow copy construction
		Airfoil(const Airfoil&) = delete;


	//- Destructor
	~Airfoil();


	// Member functions

		// Maybe try and implement through ManipulatorInterface?
		// should be a ShapeBase (reimplement shape after
		// NacaProfileGenerator is tested
		// should also give some way to access surfacePoints_

		//- Scale to chord
		void scaleToChord(const double chord) const;			// not implemented

		//- Translate along vector
		void translateAlongVector(const Vector& vector) const;	// not implemented

		//- Align center of mass with point
		void centerOnPoint(const Point& point) const;			// not implemented

		//- Rotate around center of mass by 'angle' degrees
		void rotateAroundCenter(const double angle) const;		// not implemented

		//- Project to surface along vector
		void projectAlongVector
		(
			const Shape& shape,
			const Vector& vector
		) const;												// not implemented


	// Member operators
	
		//- Disallow assignment
		Airfoil& operator=(const Airfoil&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
