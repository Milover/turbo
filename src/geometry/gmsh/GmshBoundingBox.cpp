/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshBoundingBox.h"

#include "Error.h"
#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Pair<Vector> GmshBoundingBox::execute
(
	const std::size_t tag,
	const Integer dimension
) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	Vector min {0.0, 0.0};
	Vector max {0.0, 0.0};

	try
	{
		gmsh::model::getBoundingBox
		(
			dimension,
			static_cast<Integer>(tag),
			min.x(),
			min.y(),
			min.z(),
			max.x(),
			max.y(),
			max.z()
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

	return Pair<Vector> {min, max};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Pair<Vector> GmshBoundingBox::operator()
(
	const std::size_t tag,
	const Integer dimension
) const noexcept(ndebug)
{
	return execute(tag, dimension);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
