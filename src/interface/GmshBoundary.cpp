/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshBoundary.h"

#include "Error.h"
#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

std::vector<std::size_t> GmshBoundary::execute
(
	const std::size_t tag,
	const Integer dimension
) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	Vectorpair<Integer> dimTags;

	try
	{
		gmsh::model::getBoundary
		(
			Vectorpair<Integer>
			{
				{dimension, static_cast<Integer>(tag)}
			},
			dimTags,
			false,		// not combined
			false,		// not oriented
			false		// not recursive
		);
	}
	catch(...)
	{
		error
		(
			FUNC_INFO,
			"nonexistent entity [dim, tag]: [", dimension, ", ", tag, "]"
		);
	}

	std::vector<std::size_t> tags;
	tags.reserve(dimTags.size());

	for (auto [d, t] : dimTags)
		tags.emplace_back
		(
			static_cast<std::size_t>(t)
		);

	return tags;
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::vector<std::size_t> GmshBoundary::operator()
(
	const std::size_t tag,
	const Integer dimension
) const noexcept(ndebug)
{
	return execute(tag, dimension);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
