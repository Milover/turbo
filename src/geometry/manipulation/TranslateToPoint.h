/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::TranslateToPoint

Description
	Class TranslateToPoint

SourceFiles
	TranslateToPoint.cpp

\*---------------------------------------------------------------------------*/

#ifndef TRANSLATE_TO_POINT_H
#define TRANSLATE_TO_POINT_H

#include "TranslateBase.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class TranslateToPoint Declaration
\*---------------------------------------------------------------------------*/

class TranslateToPoint final
:
	public TranslateBase<Point, Point>
{
public:

	// Constructors

		//- Default constructor
		TranslateToPoint() = default;

		//- Disallow copy construction
		TranslateToPoint(const TranslateToPoint&) = delete;


	//- Destructor
	~TranslateToPoint();


	// Member functions

		//- Set translation vector
		void setParameters
		(
			const Point& fromPoint,
			const Point& toPoint
		) noexcept override;


	// Member operators

		//- Disallow assignment
		TranslateToPoint& operator=(const TranslateToPoint&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
