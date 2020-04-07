/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Surface

Description
	A dummy base class to help differentiate surface classes

SourceFiles
	Surface.cpp

\*---------------------------------------------------------------------------*/

#ifndef SURFACE_H
#define SURFACE_H

#include <vector>

#include "Point.h"
#include "Shape.h"
#include "Wire.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Surface Declaration
\*---------------------------------------------------------------------------*/

class Surface
:
	public Shape
{
protected:

	typedef std::vector<Wire> Wirevector;
	typedef std::vector<Point> Pointvector;


	// Constructors

		//- Construct from tag
		Surface(const int tag) noexcept;


public:

	// Constructors

		//- Copy constructor
		Surface(const Surface&) = default;

		//- Move constructor
		Surface(Surface&&) = default;


	//- Destructor
	virtual ~Surface() = default;


	// Member operators

		//- Disallow assignment
		Surface& operator=(const Surface&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
