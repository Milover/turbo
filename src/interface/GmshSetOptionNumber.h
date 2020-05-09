/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSetOptionNumber

Description
	GmshSetOptionNumber class

SourceFiles
	GmshSetOptionNumber.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_OPTION_NUMBER_H
#define INTERFACE_GMSH_OPTION_NUMBER_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
					Class GmshSetOptionNumber Declaration
\*---------------------------------------------------------------------------*/

struct GmshSetOptionNumber
{
	//- Set a gmsh number option
	void operator()
	(
		const String& variable,
		const Float value
	) const noexcept;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
