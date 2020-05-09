/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include <gmsh.h>

#include "GmshTransfinite.h"

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "GmshBase.h"
#include "GmshControl.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void GmshTransfinite::execute
(
	const geometry::Curve* curve,
	const String& distribution,
	const Integer numSegments,
	const Float scaleFactor
) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	gmsh::model::mesh::setTransfiniteCurve
	(
		static_cast<Integer>(curve->tag()),
		numSegments + 1,		// because the function takes number of nodes
		distribution,
		scaleFactor
	);
}


void GmshTransfinite::execute
(
	const geometry::Surface* surface
) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	GmshBase::synchronize();

	auto& corners {surface->cornersCRef()};

	Intvector tags;
	tags.reserve(corners.size());

	for (auto& c : corners)
		tags.emplace_back
		(
			static_cast<Integer>(c->tag())
		);

	gmsh::model::mesh::setTransfiniteSurface
	(
		static_cast<Integer>(surface->tag()),
		"Left",		// arrangement
		tags
	);
}

/*
void GmshTransfinite::execute(const Volume* volume) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	auto& corners {volume->cornersCRef()};	// XXX: unimplemented

	Intvector tags;
	tags.reserve(corners.size());

	for (auto& c : corners)
		tags.emplace_back
		(
			static_cast<Integer>(c->tag())
		);

	gmsh::model::mesh::setTransfiniteVolume
	(
		static_cast<Integer>(volume->tag()),
		tags
	);
}
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace turbo

// ************************************************************************* //
