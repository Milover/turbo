/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::interface::GmshBoundary

	WARNING: The gmsh function doesn't always work as one would expect.
			 Godspeed brave adventurer.

Description
	GmshBoundary class

SourceFiles
	GmshBoundary.cpp

\*---------------------------------------------------------------------------*/

#ifndef INTERFACE_GMSH_BOUNDARY_H
#define INTERFACE_GMSH_BOUNDARY_H

#include <type_traits>

#include "Entity.h"
#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

/*---------------------------------------------------------------------------*\
						Class GmshBoundary Declaration
\*---------------------------------------------------------------------------*/

class GmshBoundary
{
private:

	//- Execute boundary (tag) retrieval
	std::vector<std::size_t> execute
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept(ndebug);


public:

	//- Get boundary entities (tags) of geometry,
	//	NOTE:
	//		- non-recursive
	//		- calls GmshBase::synchronize()
	template
	<
		typename Geometry,
		typename = std::enable_if_t<geometry::isEntity_v<Geometry>>
	>
	std::vector<std::size_t> operator()(const Geometry* g) const noexcept;

	//- Get boundary entities (tags) of geometry,
	//	NOTE:
	//		- non-recursive
	//		- calls GmshBase::synchronize()
	std::vector<std::size_t> operator()
	(
		const std::size_t tag,
		const Integer dimension
	) const noexcept(ndebug);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
std::vector<std::size_t>
GmshBoundary::operator()(const Geometry* g) const noexcept
{
	return execute(g->tag(), g->dim);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
