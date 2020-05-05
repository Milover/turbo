/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Definitions of some utility functions used in unit tests for surface
	classes.

\*---------------------------------------------------------------------------*/

#ifndef TEST_SURFACES_H
#define TEST_SURFACES_H

#include <algorithm>
#include <vector>

#include <gmsh.h>

#include "Surface.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace test
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Check surface dimensions
bool checkSurfaceDimension(const std::vector<Uptr<geometry::Surface>>& surfaces)
{
	bool check {true};

	for (auto& s : surfaces)
		check = check && s->dim == 2;

	return check;
}


//- Check surface tags
bool checkSurfaceTags(const std::vector<Uptr<geometry::Surface>>& surfaces)
{
	bool check {true};

	for (std::size_t i {0}; i < surfaces.size(); ++i)
		if (check)
			check = surfaces[i]->tag() == i + 1;

	return check;
}


//- Check boundary curves
bool checkSurfaceBoundary(const std::vector<Uptr<geometry::Surface>>& surfaces)
{
	auto vectorCmp = [](const auto& v1, const auto& v2)
	{
		if (v1.size() != v2.size())
			return false;

		bool check {true};
		for (auto i {v1.size()}; i < v1.size(); ++i)
			check = check
				 && v1[i] == v2[i];

		return check;
	};

	bool check {true};

	gmsh::model::occ::synchronize();

	for (auto& s : surfaces)
	{
		Vectorpair<Integer> dimTags;

		gmsh::model::getBoundary
		(
			Vectorpair<Integer>
			{
				{s->dim, static_cast<Integer>(s->tag())}
			},
			dimTags,
			false,		// combined
			false,		// oriented
			false		// recursive
		);

		std::vector<std::size_t> curveTags;
		std::vector<std::size_t> boundaryTags;

		for (auto [dim, tag] : dimTags)
			curveTags.push_back(static_cast<std::size_t>(tag));

		auto& boundary {s->boundaryRef()};
		for (auto& b : boundary)
			boundaryTags.push_back(b->tag());

		std::sort(curveTags.begin(), curveTags.end());
		std::sort(boundaryTags.begin(), boundaryTags.end());

		check = check && vectorCmp(curveTags, boundaryTags);
	}

	return check;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace test
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
