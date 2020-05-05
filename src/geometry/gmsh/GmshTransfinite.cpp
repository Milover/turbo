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
#include "GmshControl.h"
#include "Surface.h"
#include "Volume.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace interface
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void GmshTransfinite::execute
(
	const Curve* curve,
	const String& distribution,
	const Integer numSegments,
	const Float scaleFactor
) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	if (numSegments <= 0)
		error(FUNC_INFO, "number of segments < 0");

	gmsh::model::mesh::setTransfiniteCurve
	(
		static_cast<Integer>(curve->tag()),
		numSegments + 1,		// because the function takes number of nodes
		distribution,
		scaleFactor
	);
}


void GmshTransfinite::execute(const Surface* surface) const noexcept(ndebug)
{
	assert(GmshControl::initialized());

	auto& corners {surface->cornersRef()};

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

	auto& corners {volume->cornersRef()};	// NOTE: unimplemented

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

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void GmshTransfinite::operator()
(
	const Curve* curve,
	const Distribution distribution,
	const Integer numSegments,
	const Float scaleFactor
) const noexcept(ndebug)
{
	String distributionType;

	if (distribution == GmshTransfinite::PROGRESSION)
		distributionType = "Progression";
	else
		distributionType = "Bump";

	execute
	(
		curve,
		distributionType,
		numSegments,
		scaleFactor
	);
}


void GmshTransfinite::operator()(const Surface* surface) const noexcept(ndebug)
{
	execute(surface);
}

/*
void GmshTransfinite::operator()(const Volume* volume) const noexcept(ndebug)
{
	execute(volume);
}
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace interface
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
