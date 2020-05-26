/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshSpline.h"

#include "General.h"
#include "GmshControl.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

std::size_t GmshSpline::operator()
(
	const std::size_t tag,
	const geometry::Point& start,
	const std::vector<geometry::Point>& points,
	const geometry::Point& end
) const noexcept
{
	assert(GmshControl::initialized());

	std::vector<Integer> tags;
	tags.reserve(points.size() + 2);

	// assemble tags
	tags.emplace_back(start.tag());

	for (auto& p : points)
		tags.emplace_back(p.tag());

	tags.emplace_back(end.tag());

	return static_cast<std::size_t>
	(
		gmsh::model::occ::addSpline
		(
			tags,
			static_cast<Integer>(tag)
		)
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
