/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshPhysicalGroup

Description
	GmshPhysicalGroup class

SourceFiles
	GmshPhysicalGroup.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_PHYSICAL_GROUP_H
#define INTERFACE_GMSH_PHYSICAL_GROUP_H

#include <type_traits>

#include "Entity.h"
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
					Class GmshPhysicalGroup Declaration
\*---------------------------------------------------------------------------*/

class GmshPhysicalGroup
{
private:

	//- Execute
	std::size_t execute
	(
		const Integer groupDim,
		const String& groupName,
		const Intvector& tags
	) const noexcept;


public:

	//- Create a physical group from geometry
	template
	<
		typename Grp,
		typename Geo,
		typename = std::enable_if_t<mesh::isGroup_v<Grp>>,
		typename = std::enable_if_t<geometry::isEntity_v<Geo>>
	>
	[[maybe_unused]] std::size_t operator()
	(
		const Grp* group,
		const Sptrvector<Geo>& geometry
	) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Grp, typename Geo, typename, typename>
std::size_t GmshPhysicalGroup::operator()
(
	const Grp* group,
	const Sptrvector<Geo>& geometry
) const noexcept
{
	Intvector tags;
	tags.reserve(geometry.size());

	for (auto& g : geometry)
		tags.emplace_back(static_cast<Integer>(g->tag()));

	return execute
	(
		group->dim(),
		group->name(),
		tags
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
