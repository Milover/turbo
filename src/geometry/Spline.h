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

#ifndef GEOMETRY_SPLINE_H
#define GEOMETRY_SPLINE_H

#include "Curve.h"
#include "General.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Spline Declaration
\*---------------------------------------------------------------------------*/

class Spline final
:
	public Curve
{
protected:

	// Member functions

		//- Construct spline geometry
		Integer construct
		(
			Point start,
			Point end,
			const Pointvector& points
		) const noexcept;


public:

	// Constructors

		//- Construct from a vector of points
		//  (the start-end points are copied to
		//  avoid dependency issues)
		Spline(const Pointvector& points) noexcept;

		//- Copy constructor
		Spline(const Spline&) = default;

		//- Copy constructor
		Spline(Spline&&) = default;


	//- Destructor
	~Spline() = default;


	// Member operators

		//- Disallow copy assignment
		Spline& operator=(const Spline&) = delete;

		//- Disallow move assignment
		Spline& operator=(Spline&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
