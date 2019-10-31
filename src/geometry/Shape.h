/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

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

#include "gmsh.h"
#include "Utility.h"
//#include "Vector.h"

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
		void remove() const;

		//- Copy Shape geometry and return tag
		int copy() const;


protected:

	// Protected data
	

	// Constructors
		
		//- Construct from tag
		Shape(const std::pair<int, int> dimTag);

		//- Construct from a Shape
		Shape(const Shape&);


	// Member functions


public:

	// Constructors
	

	//- Destructor
	virtual ~Shape();


	// Member functions
		
		//- Return Shape dimTag
		std::pair<int, int> getDimTag() const;

		//- Get dimTags of Shapes on boundary of Shape
		void getBoundary(Vectorpair<int>& dimTags) const;

		//- Get Shape bounding box coordinates (min, max)
		Vectorpair<double> getBoundingBox() const;

		//- Get Shape center of mass coordinates
		std::vector<double> getCenterOfMass() const;

		//- Return minimum distance vector to Shape
		//virtual Vector getMinDistance(const Shape&) const = 0;

		//- Return name of Shape
		std::string getName() const;

		//- Set name of Shape
		void setName(const std::string& name);


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
