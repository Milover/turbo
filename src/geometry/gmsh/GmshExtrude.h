/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshExtrude

Description
	GmshExtrude class

SourceFiles
	GmshExtrude.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_EXTRUDE_H
#define GEOMETRY_INTERFACE_GMSH_EXTRUDE_H

#include <vector>

#include "Entity.h"
#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshExtrude Declaration
\*---------------------------------------------------------------------------*/

class GmshExtrude
{
private:

	//- Execute extrusion
	[[nodiscard]] std::vector<std::size_t> execute
	(
		const std::size_t tag,
		const Integer dimension,
		const Vector& v
	) const noexcept;


public:

	//- Create an extrusion, return the tags
	//	NOTE: the return order is:
	//		tags[0]		- shape (of order Geometry::dim) opposite of base
	//		tags[1]		- the extrusion i.e. shape (of order Geometry::dim + 1)
	//		tags[...]	- other shapes (of order Geometry::dim) excluding base
	template
	<
		typename Geometry,
		typename = std::enable_if_t<isEntity_v<Geometry>>
	>
	[[nodiscard]] std::vector<std::size_t> operator()
	(
		const Geometry* base,
		const Vector& direction
	) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
std::vector<std::size_t> GmshExtrude::operator()
(
	const Geometry* base,
	const Vector& direction
) const noexcept
{
	return execute
	(
		base->tag(),
		base->dim,
		direction
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
