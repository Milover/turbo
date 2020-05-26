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

#include "Entity.h"
#include "General.h"
#include "PlaceholderPoint.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Point Declaration
\*---------------------------------------------------------------------------*/

class Point final
:
	public Shape<Entity0D>
{
private:

	// Private data

		Coordinates coords_;


	// Member functions

		//- Construct the geometry
		void construct() const noexcept;


public:

	// Constructors

		//- Construct from raw floats
		Point
		(
			const Float x,
			const Float y,
			const Float z = 0.0
		) noexcept;

		//- Construct from a placeholder point
		Point(const detail::PlaceholderPoint& p) noexcept;

		//- Construct from coordinates
		Point(const Coordinates& c) noexcept;

		//- Construct from coordinates
		Point(Coordinates&& c) noexcept;

		//- Copy constructor
		Point(const Point&) = delete;

		//- Copy constructor
		Point(Point&&) = default;


	//- Destructor
	~Point() noexcept;


	// Member functions

		//- Get coordinates
		Coordinates coordinates() const noexcept;

		//- Return origin
		static Point origin() noexcept;


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
