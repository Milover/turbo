/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::BasicManipulator

Description
	Base class template for basic Shape manipulation

SourceFiles
	BasicManipulator.cpp

\*---------------------------------------------------------------------------*/

#ifndef BASIC_MANIPULATOR_H
#define BASIC_MANIPULATOR_H

#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class BasicManipulator Declaration
\*---------------------------------------------------------------------------*/

class BasicManipulator
{
private:

	// Private data
	

	// Member functions
		
		//- Translate Shapes defined by dimTags along a vector
		void translate
		(
			const Vectorpair<int>& dimTag,
			const double dx,
			const double dy,
			const double dz
		);								// not implemented

		//- Scale Shapes defined by dimTags by factors relative to base point
		void scale
		(
			const Vectorpair<int>& dimTag,
			const double dx,
			const double dy,
			const double dz,
			const Point& point
		);								// not implemented

		//- Rotate Shapes defined by dimTags 'angle' degrees around an axis
		void rotate
		(
			const Vectorpair<int>& dimTag,
			const double dx,
			const double dy,
			const double dz,
			const Point& point,
			const double angle
		);								// not implemented


protected:

	// Protected data


	// Constructors
		
		//- Default constructor
		BasicManipulator();
	

	// Member functions


public:
	
	// Constructors
	

	//- Destructor
	~BasicManipulator();


	// Member functions
		
		//- Translate Shape along vector
		void translateAlongVector();		// not implemented

		//- Translate Shapes along vector
		void translateAlongVector();		// not implemented

		//- Translate Shape to Point
		void translateToPoint();			// not implemented

		//- Scale Shape nonuniformly
		void scaleNonUniform();				// not implemented

		//- Scale Shapes nonuniformly
		void scaleNonUniform();				// not implemented

		//- Scale Shape uniformly
		void scaleUniform();				// not implemented

		//- Scale Shape uniformly
		void scaleUniform();				// not implemented

		//- Rotate Shape by angle
		void rotateByAngle();				// not implemented

		//- Rotate Shapes by angle
		void rotateByAngle();				// not implemented


	// Member operators


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
