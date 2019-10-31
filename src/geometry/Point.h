/*---------------------------------------------------------------------------*\

Header

-------------------------------------------------------------------------------
License

Class
	turbo::geometry::Point

Description
	Point class

SourceFiles
	Point.cpp

\*---------------------------------------------------------------------------*/

#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

#include "gmsh.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// Forward declarations

/*---------------------------------------------------------------------------*\
						Class Line Declaration
\*---------------------------------------------------------------------------*/

class Point
:
	public Shape
{
private:

	// Private data

	
	// Member functions


protected:

	// Protected data
	

	// Member functions

		//- Construct Point geometry
		virtual int construct
		(
			const double x,
			const double y,
			const double z
		) const;


public:
	
	// Constructors
		
		//- Construct from coordinates
		Point
		(
			const double x,
			const double y,
			const double z = 0.0
		);

		//- Construct from a Point
		Point(const Point&);


	//- Destructor
	virtual ~Point();

	// Member functions
		
		//- Get Point coordinates
		std::vector<double> getCoordinates() const;


	// Member operators
	
		//- Disallow assignment
		Point& operator=(const Point&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
