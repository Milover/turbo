/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshWrite

Description
	GmshWrite class

SourceFiles
	GmshWrite.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_WRITE_H
#define INTERFACE_GMSH_WRITE_H

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
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
	void operator()(const Path& file) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
