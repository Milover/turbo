/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Shape

Description
	Abstract base class for geometry objects

SourceFiles
	Shape.cpp

\*---------------------------------------------------------------------------*/

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <utility>
#include <vector>

#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{


// Forward declarations

/*---------------------------------------------------------------------------*\
						Class Shape Declaration
\*---------------------------------------------------------------------------*/

class Shape
{
private:

	// Private data
	
		const std::pair<int, int> dimTag_;


	// Member functions

		//- Remove Shape geometry
		void remove() const noexcept;

		//- Copy Shape geometry and return tag
		int copy() const noexcept;


protected:

	// Protected data
	

	// Constructors
		
		//- Construct from tag
		Shape(const std::pair<int, int> dimTag) noexcept;

		//- Construct from a Shape
		Shape(const Shape&) noexcept;


	// Member functions


public:

	// Constructors
	

	//- Destructor
	virtual ~Shape() noexcept;


	// Member functions
		
		//- Return Shape dimTag
		std::pair<int, int> getDimTag() const noexcept;

		//- Get dimTags of Shapes on boundary of Shape
		void getBoundary(Vectorpair<int>& dimTags) const noexcept;

		//- Get Shape bounding box coordinates (min, max)
		Vectorpair<double> getBoundingBox() const noexcept;

		//- Get Shape center of mass coordinates
		//std::vector<double> getCenterOfMass() const noexcept;		// implement later

		//- Return minimum distance vector to Shape
		//virtual Vector getMinDistance(const Shape&) const = 0;	// implement later

		//- Return name of Shape
		std::string getName() const noexcept;

		//- Set name of Shape
		void setName(const std::string& name) noexcept;


	// Member operators

		//- Disallow assignment
		Shape& operator=(const Shape&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
