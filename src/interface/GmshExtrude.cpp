/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>
#include <vector>

#include <gmsh.h>

#include "GmshExtrude.h"

#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

std::vector<std::size_t> GmshExtrude::execute
(
	const std::size_t tag,
	const Integer dimension,
	const Vector& v
) const noexcept
{
	assert(GmshControl::initialized());
	assert(dimension < 3);

	// because we're about to create free floating geometry
	GmshBase::unsynchronize();

	Vectorpair<Integer> dimTags;

	Intvector nElements;
	Floatvector heights;
	bool recombine {false};

	if (dimension == 2)
	{
		nElements.push_back(1);
		heights.push_back(1);
		recombine = true;
	};

	gmsh::model::occ::extrude
	(
		Vectorpair<Integer>
		{
			{dimension, static_cast<Integer>(tag)}
		},
		v.x(),
		v.y(),
		v.z(),
		dimTags,
		nElements,
		heights,
		recombine
	);

	std::vector<std::size_t> tags;
	tags.reserve(dimTags.size());

	for (auto [d, t] : dimTags)
		tags.emplace_back
		(
			static_cast<std::size_t>(t)
		);

	return tags;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
