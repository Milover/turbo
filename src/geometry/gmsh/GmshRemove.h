/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshRemove

Description
	GmshRemove class

SourceFiles
	GmshRemove.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_REMOVE_H
#define GEOMETRY_INTERFACE_GMSH_REMOVE_H

#include <type_traits>

#include "Entity.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshRemove Definition
\*---------------------------------------------------------------------------*/

class GmshRemove
{
private:

	//- Execute removal
	void execute
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept;


public:

	//- Remove geometry
	template
	<
		typename Geometry,
		typename = std::enable_if_t<isEntity_v<Geometry>>
	>
	void operator()(const Geometry* g) const noexcept;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
void GmshRemove::operator()(const Geometry* g) const noexcept
{
	execute(g->tag(), g->dim);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
