/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshTransfinite

Description
	GmshTransfinite class

	NOTE: transfinite volumes not implemented

SourceFiles
	GmshTransfinite.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_TRANSFINITE_H
#define GEOMETRY_INTERFACE_GMSH_TRANSFINITE_H

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "Surface.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshTransfinite Declaration
\*---------------------------------------------------------------------------*/

class GmshTransfinite
{
private:

	//- Execute
	void execute
	(
		const Curve* curve,
		const String& distribution,
		const Integer numSegments,
		const Float scaleFactor
	) const noexcept(ndebug);

	//- Execute
	void execute(const Surface* surface) const noexcept(ndebug)

	//- Execute
	//	NOTE: corners not implemented for volumes
	//void execute(const Volume* volume) const noexcept(ndebug)


public:

	enum class Distribution
	{
		PROGRESSION,
		BUMP
	};

	//- Designate a curve for transfinite meshing
	void operator()
	(
		const Curve* curve,
		const Distribution distribution,
		const Integer numSegments,
		const Float scaleFactor
	) const noexcept(ndebug);

	//- Designate a surface for transfinite meshing
	void operator()(const Surface* surface) const noexcept(ndebug);

	//- Designate a volume for transfinite meshing
	//	NOTE: corners not implemented for volumes
	//void operator()(const Volume* volume) const noexcept(ndebug);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
