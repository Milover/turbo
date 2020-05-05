/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::detail::PlaceholderCurve

Description
	PlaceholderCurve class

SourceFiles
	PlaceholderCurve.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_PLACEHOLDER_CURVE_H
#define GEOMETRY_DETAIL_PLACEHOLDER_CURVE_H

#include "Error.h"
#include "General.h"
#include "PlaceholderPoint.h"
#include "PlaceholderShape.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

/*---------------------------------------------------------------------------*\
						Class PlaceholderCurve Declaration
\*---------------------------------------------------------------------------*/

class PlaceholderCurve final
:
	public PlaceholderShape
{
private:

	// Private Data

		Vectorpair<PlaceholderPoint, Sptr<Point>> boundary_;


public:

	// Constructors

		//- Construct from a tag and get the boundary curves
		explicit PlaceholderCurve(const std::size_t t) noexcept(ndebug);


	// Member functions

		//- Get boundary points
		Vectorpair<PlaceholderPoint, Sptr<Point>> boundary() const noexcept;

		//- Store a point sptr if it refers to
		//	a boundary point placeholder
		void tryStore(const Sptr<Point>& point) noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
