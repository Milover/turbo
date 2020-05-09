/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshCopy

Description
	GmshCopy class

SourceFiles
	GmshCopy.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_BOUNDARY_H
#define INTERFACE_GMSH_BOUNDARY_H

#include <type_traits>

#include "Entity.h"
#include "Error.h"
#include "General.h"
#include "GeometryDetailGeneral.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
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
		typename = std::enable_if_t<geometry::isEntity_v<Geometry>>
	>
	auto operator()(const Geometry* g) const noexcept;

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
auto GmshCopy::operator()(const Geometry* g) const noexcept
{
	return geometry::detail::GeometryBaseType_t<Geometry>
	{
		geometry::detail::GeometryPlaceholderType_t<Geometry> {execute(g)}
	};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
