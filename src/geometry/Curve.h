/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Curve

Description
	A dummy base class to help differentiate curve classes

SourceFiles
	Curve.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_CURVE_H
#define GEOMETRY_CURVE_H

#include <vector>

#include "General.h"
#include "Point.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Curve Declaration
\*---------------------------------------------------------------------------*/

class Curve
:
	public Shape
{
protected:

	using Pointvector = std::vector<Point>;


	// Constructors

		//- Construct from tag
		Curve(const Integer tag) noexcept;


public:

	// Constructors

		//- Copy constructor
		Curve(const Curve&) = default;

		//- Move constructor
		Curve(Curve&&) = default;


	//- Destructor
	virtual ~Curve() = default;


	// Member operators

		//- Disallow copy assignment
		Curve& operator=(const Curve&) = delete;

		//- Disallow move assignment
		Curve& operator=(Curve&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
