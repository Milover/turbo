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

#include <utility>
#include <type_traits>

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
private:

	// Member functions

		//- Construct the geometry
		void construct() const noexcept;


public:

	// Constructors

		//- Construct from Coordinates
		template<typename T1, typename T2>
		Line(T1 start, T2 end);

		//- Copy constructor
		Line(const Line&) = delete;

		//- Construct from a Line
		Line(Line&&) = default;


	//- Destructor
	~Line() = default;


	// Member operators
	
		//- Disallow copy assignment
		Line& operator=(const Line&) = delete;

		//- Disallow copy assignment
		Line& operator=(Line&&) = delete;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T1, typename T2>
Line::Line(T1 end, T2 start)
{
	storeStartAndEnd
	(
		std::forward<T1>(start),
		std::forward<T2>(end)
	);

	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
