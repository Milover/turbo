/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshRemovePhysicalGroup

Description
	GmshRemovePhysicalGroup class

SourceFiles
	GmshRemovePhysicalGroup.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_REMOVE_PHYSICAL_GROUP_H
#define INTERFACE_GMSH_REMOVE_PHYSICAL_GROUP_H

#include <type_traits>

#include "General.h"
#include "Group.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// Forward declarations
namespace mesh
{
	template<typename T>
	inline constexpr bool isGroup_v;
}

namespace interface
{

/*---------------------------------------------------------------------------*\
				Class GmshRemovePhysicalGroup Declaration
\*---------------------------------------------------------------------------*/

class GmshRemovePhysicalGroup
{
private:

	//- Execute removal
	void execute
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept;


public:

	//- Remove a group
	template
	<
		typename Grp,
		typename = std::enable_if_t<mesh::isGroup_v<Grp>>
	>
	void operator()(const Grp* group) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Grp, typename>
void GmshRemovePhysicalGroup::operator()(const Grp* group) const noexcept
{
	execute(group->tag(), group->dim());
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
