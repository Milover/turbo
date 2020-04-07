/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::SurfaceSection

Description
	SurfaceSection class

SourceFiles
	SurfaceSection.cpp

\*---------------------------------------------------------------------------*/

#ifndef SURFACE_SECTION_H
#define SURFACE_SECTION_H

#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class SurfaceSection Declaration
\*---------------------------------------------------------------------------*/

class SurfaceSection final
:
	public Surface
{
private:

	// Member functions

		//- Construct surface geometry
		int construct(Surface::Wirevector&& wires) const noexcept;


public:

	// Constructors

		//- Construct from a vector of wires
		SurfaceSection(Surface::Wirevector&& wires) noexcept;

		//- Copy constructor
		SurfaceSection(const SurfaceSection&) = default;

		//- Copy constructor
		SurfaceSection(SurfaceSection&&) = default;


	//- Destructor
	~SurfaceSection() = default;


	// Member operators

		//- Disallow assignment
		SurfaceSection& operator=(const SurfaceSection&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
