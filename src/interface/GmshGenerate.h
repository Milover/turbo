/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshGenerate

Description
	GmshGenerate class

SourceFiles
	GmshGenerate.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_GENERATE_H
#define INTERFACE_GMSH_GENERATE_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshGenerate Definition
\*---------------------------------------------------------------------------*/

struct GmshGenerate
{
	//- Generate a mesh from (active) geometry
	//	NOTE: calls GmshBase::synchronize()
	void operator()() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
