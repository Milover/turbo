/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshCopy

Description
	GmshCopy class

SourceFiles
	GmshCopy.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_BOUNDARY_H
#define GEOMETRY_INTERFACE_GMSH_BOUNDARY_H

#include <type_traits>

#include "Entity.h"
#include "Error.h"
#include "General.h"
#include "GeometryDetailGeneral.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshCopy Declaration
\*---------------------------------------------------------------------------*/

class GmshCopy
{
private:

	//- Execute copy
	std::size_t execute
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept;


public:

	//- Copy geometry
	template
	<
		typename Geometry,
		typename = std::enable_if_t<isEntity_v<Geometry>>
	>
	auto operator()(const Geometry* g) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
auto GmshCopy::operator()(const Geometry* g) const noexcept
{
	return detail::GeometryBaseType_t<Geometry>
	{
		detail::GeometryPlaceholderType_t {execute(g)}
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
