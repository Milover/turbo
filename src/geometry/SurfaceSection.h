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

#ifndef GEOMETRY_SURFACE_SECTION_H
#define GEOMETRY_SURFACE_SECTION_H

#include "General.h"
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
		Integer construct(Surface::Wirevector&& wires) const noexcept;


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

		//- Disallow copy assignment
		SurfaceSection& operator=(const SurfaceSection&) = delete;

		//- Disallow move assignment
		SurfaceSection& operator=(SurfaceSection&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
