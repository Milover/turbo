/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshPoint

Description
	GmshPoint class

SourceFiles
	GmshPoint.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_POINT_H
#define INTERFACE_GMSH_POINT_H

#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshPoint Definition
\*---------------------------------------------------------------------------*/

struct GmshPoint
{
	//- Create a point
	[[maybe_unused]] std::size_t operator()
	(
		const std::size_t tag,
		const Vector& coords
	) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
