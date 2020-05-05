/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::SurfaceFilling

Description
	SurfaceFilling class

SourceFiles
	SurfaceFilling.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_SURFACE_FILLING_H
#define GEOMETRY_SURFACE_FILLING_H

#include "General.h"
#include "Surface.h"
#include "Wire.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class SurfaceFilling Declaration
\*---------------------------------------------------------------------------*/

class SurfaceFilling final
:
	public Surface
{
private:

	// Member functions

		//- Construct surface geometry
		Integer construct
		(
			Wire&& wire,
			const Pointvector& points
		) const noexcept;


public:

	// Constructors

		//- Construct from a closed wire (loop),
		//  interpolate through points if provided
		SurfaceFilling
		(
			Wire&& wire,
			const Pointvector& points = Pointvector {}
		) noexcept;

		//- Copy constructor
		SurfaceFilling(const SurfaceFilling&) = default;

		//- Copy constructor
		SurfaceFilling(SurfaceFilling&&) = default;


	//- Destructor
	~SurfaceFilling() = default;


	// Member operators

		//- Disallow copy assignment
		SurfaceFilling& operator=(const SurfaceFilling&) = delete;

		//- Disallow move assignment
		SurfaceFilling& operator=(SurfaceFilling&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
