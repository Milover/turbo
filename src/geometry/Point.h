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

#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H

#include "General.h"
#include "Shape.h"

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
			const Float x,
			const Float y,
			const Float z
		) const noexcept;


public:

	// Constructors
		
		//- Construct from raw coordinates
		Point
		(
			const Float x,
			const Float y,
			const Float z = 0.0
		) noexcept;

		//- Construct from point coordinates
		Point(const Point::Coordinates& c) noexcept;

		//- Copy constructor
		Point(const Point&) = default;

		//- Copy constructor
		Point(Point&&) = default;


	//- Destructor
	~Point() = default;


	// Member functions

		//- Get coordinates
		Point::Coordinates coordinates() const noexcept;

		//- Return origin
		static Point origin();


	// Member operators
	
		//- Disallow copy assignment
		Point& operator=(const Point&) = delete;

		//- Disallow move assignment
		Point& operator=(Point&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
