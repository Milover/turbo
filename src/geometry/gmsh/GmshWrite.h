/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshWrite

Description
	GmshWrite class

SourceFiles
	GmshWrite.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_WRITE_H
#define GEOMETRY_INTERFACE_GMSH_WRITE_H

#include <type_traits>

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshWrite Declaration
\*---------------------------------------------------------------------------*/

struct GmshWrite
{
	//- Write the geometry (current active model) to a file,
	//	file extension determines output file type (see gmsh manual)
	//	NOTE: calls GmshBase::synchronize()
	void operator()(const String& filename) const noexcept(ndebug);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
