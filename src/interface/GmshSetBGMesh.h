/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshSetBGMesh

Description
	GmshSetBGMesh class

SourceFiles
	GmshSetBGMesh.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_SET_BG_MESH_H
#define INTERFACE_GMSH_SET_BG_MESH_H

#include <type_traits>

#include "General.h"
#include "SizeFieldBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshSetBGMesh Definition
\*---------------------------------------------------------------------------*/

class GmshSetBGMesh
{
private:

	//- Execute
	void execute(const std::size_t tag) const noexcept;


public:

	//- Set field as background mesh
	template
	<
		typename Field,
		typename = std::enable_if_t
		<
			std::is_base_of_v<mesh::SizeFieldBase, Field>
		>
	>
	void operator()(const Field* f) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Field, typename>
void GmshSetBGMesh::operator()(const Field* f) const noexcept
{
	execute(f->tag());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
