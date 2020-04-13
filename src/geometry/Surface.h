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

#ifndef GEOMETRY_SURFACE_H
#define GEOMETRY_SURFACE_H

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

	using Wirevector = std::vector<Wire>;
	using Pointvector = std::vector<Point>;


	// Constructors

		//- Construct from tag
		Surface(const Integer tag) noexcept;


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
