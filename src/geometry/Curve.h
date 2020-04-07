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

#ifndef CURVE_H
#define CURVE_H

#include <vector>

#include "Shape.h"
#include "Point.h"

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

	typedef std::vector<Point> Pointvector;


	// Constructors

		//- Construct from tag
		Curve(const int tag) noexcept;


public:

	// Constructors

		//- Copy constructor
		Curve(const Curve&) = default;

		//- Move constructor
		Curve(Curve&&) = default;


	//- Destructor
	virtual ~Curve() = default;


	// Member operators

		//- Disallow assignment
		Curve& operator=(const Curve&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
