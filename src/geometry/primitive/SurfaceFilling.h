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

#ifndef SURFACE_FILLING_H
#define SURFACE_FILLING_H

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
		int construct
		(
			Wire&& wire,
			const Surface::Pointvector& points
		) const noexcept;


public:

	// Constructors

		//- Construct from a closed wire (loop),
		//  interpolate through points if provided
		SurfaceFilling
		(
			Wire&& wire,
			const Surface::Pointvector& points = Pointvector {}
		) noexcept;

		//- Copy constructor
		SurfaceFilling(const SurfaceFilling&) = default;

		//- Copy constructor
		SurfaceFilling(SurfaceFilling&&) = default;


	//- Destructor
	~SurfaceFilling() = default;


	// Member operators

		//- Disallow assignment
		SurfaceFilling& operator=(const SurfaceFilling&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
