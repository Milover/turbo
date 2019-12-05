/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Spline

Description
	Spline class

SourceFiles
	Spline.cpp

\*---------------------------------------------------------------------------*/

#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <initializer_list>

#include "Shape.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Spline Declaration
\*---------------------------------------------------------------------------*/

class Spline
:
	public Shape
{
protected:

	typedef std::vector<Point> Pointvector;


	// Member functions

		//- Construct spline geometry
		virtual int construct(const Pointvector& points) const noexcept;


public:

	// Constructors

		//- Construct from points
		//  (we take a copy to avoid dependency issues)
		Spline(std::initializer_list<Point> points) noexcept;

		//- Construct from a (copy of a) vector of points
		//  (we take a copy to avoid dependency issues)
		Spline(const Pointvector points) noexcept;

		//- Construct from a spline
		Spline(const Spline&) noexcept;


	//- Destructor
	virtual ~Spline() = default;


	// Member operators

		//- Disallow assignment
		Spline& operator=(const Spline&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
