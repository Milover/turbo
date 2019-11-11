/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Point

Description
	Point class

SourceFiles
	Point.cpp

\*---------------------------------------------------------------------------*/

#ifndef POINT_H
#define POINT_H

#include <vector>

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
protected:

	// Member functions

		//- Construct Point geometry
		virtual int construct
		(
			const double x,
			const double y,
			const double z
		) const noexcept;


public:
	
	// Constructors
		
		//- Construct from coordinates
		Point
		(
			const double x,
			const double y,
			const double z = 0.0
		) noexcept;

		//- Construct from a Point
		Point(const Point&) noexcept;


	//- Destructor
	virtual ~Point();

	// Member functions
		
		//- Get Point coordinates
		std::vector<double> getCoordinates() const noexcept;


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
