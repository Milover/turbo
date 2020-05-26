/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::PlanarSurface

Description
	PlanarSurface class

SourceFiles
	PlanarSurface.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_PLANAR_SURFACE_H
#define GEOMETRY_PLANAR_SURFACE_H

#include <utility>

#include "Curve.h"
#include "General.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class PlanarSurface Declaration
\*---------------------------------------------------------------------------*/

class PlanarSurface final
:
	public Surface
{
private:

	// Member functions

		//- Construct surface geometry
		void construct() noexcept;


public:

	// Constructors

		//- Construct from curves forming a closed loop
		template<typename... Curves>
		PlanarSurface(Curves&&... cs);

		//- Construct from vectors of curves (curve sptrs) forming closed loops,
		//	the first vector is the boundary, the rest are boundaries
		//	of holes within the surface
		template<typename Boundary, typename... Holes>
		PlanarSurface(Boundary&& b, Holes&&... hs);

		//- Copy constructor
		PlanarSurface(const PlanarSurface&) = delete;

		//- Copy constructor
		PlanarSurface(PlanarSurface&&) = default;


	//- Destructor
	~PlanarSurface() = default;


	// Member operators

		//- Disallow copy assignment
		PlanarSurface& operator=(const PlanarSurface&) = delete;

		//- Disallow copy assignment
		PlanarSurface& operator=(PlanarSurface&&) = delete;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename... Curves>
PlanarSurface::PlanarSurface(Curves&&... cs)
:
	Surface
	{
		std::forward<Curves>(cs)...
	}
{
	construct();
}


template<typename Boundary, typename... Holes>
PlanarSurface::PlanarSurface(Boundary&& b, Holes&&... hs)
:
	Surface
	{
		std::forward<Boundary>(b),
		std::forward<Holes>(hs)...
	}
{
	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
