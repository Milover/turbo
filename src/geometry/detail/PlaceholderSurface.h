/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::detail::PlaceholderSurface

Description
	PlaceholderSurface class

SourceFiles
	PlaceholderSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_PLACEHOLDER_SURFACE_H
#define GEOMETRY_DETAIL_PLACEHOLDER_SURFACE_H

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "PlaceholderCurve.h"
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
					Class PlaceholderSurface Declaration
\*---------------------------------------------------------------------------*/

class PlaceholderSurface final
:
	public PlaceholderShape
{
private:

	// Private Data

		Vectorpair<PlaceholderCurve, Sptr<Curve>> boundary_;


public:

	// Constructors

		//- Construct from a tag and get the boundary curves
		explicit PlaceholderSurface(const std::size_t t) noexcept(ndebug);


	// Member functions

		//- Get boundary curves
		Vectorpair<PlaceholderCurve, Sptr<Curve>> boundary() const noexcept;

		//- Store a curve sptr if it refers to
		//	a boundary curve placeholder
		void tryStore(const Sptr<Curve>& curve) noexcept;

		//- Store (propagate to boundary curves) a point sptr
		//	if it refers to a boundary point placeholder
		void tryStore(const Sptr<Point>& point) noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
