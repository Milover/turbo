/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::interface::GmshBoundingBox

Description
	GmshBoundingBox class

SourceFiles
	GmshBoundingBox.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_INTERFACE_GMSH_BOUNDING_BOX_H
#define GEOMETRY_INTERFACE_GMSH_BOUNDING_BOX_H

#include <type_traits>

#include "Entity.h"
#include "Error.h"
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
					Class GmshBoundingBox Declaration
\*---------------------------------------------------------------------------*/

class GmshBoundingBox
{
private:

	//- Execute boundary box computation
	Pair<Vector> execute
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept(ndebug);


public:

	//- Get the bounding box of an entity,
	//	returns min/max coordinates as a pair of vectors
	//	NOTE: calls GmshBase::synchronize()
	template
	<
		typename Geometry,
		typename = std::enable_if_t<isEntity_v<Geometry>>
	>
	Pair<Vector> operator()(const Geometry* g) const noexcept;

	//- Get the bounding box of an entity,
	//	returns min/max coordinates as a pair of vectors
	//	NOTE: calls GmshBase::synchronize()
	Pair<Vector> operator()
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept(ndebug);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
Pair<Vector> GmshBoundingBox::operator()(const Geometry* g) const noexcept
{
	return execute(g->tag(), g->dim);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
