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

#ifndef LINE_H
#define LINE_H

#include "Shape.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Line Declaration
\*---------------------------------------------------------------------------*/

class Line
:
	public Shape
{
protected:

	// Member functions

		//- Construct Line geometry
		virtual int construct
		(
			const int startTag,
			const int endTag
		) const noexcept;


public:
	
	// Constructors
		
		//- Construct from copies of two Points
		Line
		(
			Point start,
			Point end
		) noexcept;

		//- Construct from a Line
		Line(const Line&) noexcept;


	//- Destructor
	virtual ~Line();


	// Member functions

		//- Get Line length
		virtual double getLength() const noexcept;


	// Member operators
	
		//- Disallow assignment
		Line& operator=(const Line&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
