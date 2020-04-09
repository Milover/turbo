/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Line

Description
	Line class

SourceFiles
	Line.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H

#include "Curve.h"
#include "General.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Line Declaration
\*---------------------------------------------------------------------------*/

class Line final
:
	public Curve
{
protected:

	// Member functions

		//- Construct Line geometry
		Integer construct
		(
			const Integer startTag,
			const Integer endTag
		) const noexcept;


public:
	
	// Constructors
		
		//- Construct from copies of two Points
		Line
		(
			Point start,
			Point end
		) noexcept;

		//- Copy constructor
		Line(const Line&) = default;

		//- Construct from a Line
		Line(Line&&) = default;


	//- Destructor
	~Line() = default;


	// Member operators
	
		//- Disallow copy assignment
		Line& operator=(const Line&) = delete;

		//- Disallow move assignment
		Line& operator=(Line&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
