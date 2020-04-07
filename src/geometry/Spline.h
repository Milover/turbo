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

#include "Curve.h"
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
		int construct
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

		//- Disallow assignment
		Spline& operator=(const Spline&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
