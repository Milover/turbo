/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::detail::PlaceholderVolume

Description
	PlaceholderVolume class

SourceFiles
	PlaceholderVolume.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_VOLUME_H
#define GEOMETRY_DETAIL_VOLUME_H

#include "Curve.h"
#include "Error.h"
#include "PlaceholderSurface.h"
#include "PlaceholderShape.h"
#include "Point.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

/*---------------------------------------------------------------------------*\
					Class PlaceholderVolume Declaration
\*---------------------------------------------------------------------------*/

class PlaceholderVolume final
:
	public PlaceholderShape
{
private:

	// Private Data

		Vectorpair<PlaceholderSurface, Sptr<Surface>> boundary_;


public:

	// Constructors

		//- Construct from a tag and get the boundary surfaces
		explicit PlaceholderVolume(const std::size_t t) noexcept(ndebug);


	// Member functions

		//- Get boundary surfaces
		Vectorpair<PlaceholderSurface, Sptr<Surface>> boundary() const noexcept;

		//- Store a surface sptr if it refers to
		//	a boundary surface placeholder
		void tryStore(const Sptr<Surface>& surface) noexcept;

		//- Store (propagate to boundary surfaces) a curve sptr
		//	if it refers to a boundary curve placeholder
		void tryStore(const Sptr<Curve>& curve) noexcept;

		//- Store (propagate to boundary surface) a point sptr
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
