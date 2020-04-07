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

#include "Shape.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Line Declaration
\*---------------------------------------------------------------------------*/

class Point final
:
	public Shape
{
protected:

	// Member functions

		//- Construct Point geometry
		int construct
		(
			const double x,
			const double y,
			const double z
		) const noexcept;


public:

	// Constructors
		
		//- Construct from raw coordinates
		Point
		(
			const double x,
			const double y,
			const double z = 0.0
		) noexcept;

		//- Construct from point coordinates
		Point(const PointCoordinates& coordinates) noexcept;

		//- Copy constructor
		Point(const Point&) = default;

		//- Copy constructor
		Point(Point&&) = default;


	//- Destructor
	~Point() = default;


	// Member functions

		//- Get coordinates
		PointCoordinates getCoordinates() const noexcept;

		//- Return origin
		static Point origin();


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
