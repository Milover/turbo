/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshPhysicalGroup.h"

#include "General.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshPhysicalGroup::execute
(
	const Integer groupDim,
	const String& groupName,
	const Intvector& tags
) const noexcept
{
	assert(GmshControl::initialized());

	Integer returnTag
	{
		gmsh::model::addPhysicalGroup
		(
			groupDim,
			tags
		)
	};

	gmsh::model::setPhysicalName
	(
		groupDim,
		returnTag,
		groupName
	);

	return static_cast<std::size_t>(returnTag);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
