/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Definitions of some utility functions used in unit tests for curve classes.

\*---------------------------------------------------------------------------*/

#ifndef TEST_CURVES_H
#define TEST_CURVES_H

#include <gmsh.h>

#include "Curve.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace test
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//- Check curve dimensions
bool checkCurveDimension(const std::vector<Uptr<geometry::Curve>>& curves)
{
	bool check {true};

	for (auto& c : curves)
		if (check)
			check = c->dim == 1;;

	return check;
}


//- Check curve tags
bool checkCurveTags(const std::vector<Uptr<geometry::Curve>>& curves)
{
	bool check {true};

	for (std::size_t i {0}; i < curves.size(); ++i)
		if (check)
			check = curves[i]->tag() == i + 1;

	return check;
}


//- Check end points of curves
bool checkCurveBoundary(const std::vector<Uptr<geometry::Curve>>& curves)
{
	bool check {true};

	Vectorpair<Integer> tags;

	gmsh::model::occ::synchronize();

	for (auto& c : curves)
	{
		gmsh::model::getBoundary
		(
			Vectorpair<Integer>
			{
				{c->dim, static_cast<Integer>(c->tag())}
			},
			tags,
			false,		// combined
			false,		// oriented
			false		// recursive
		);

		if (check)
			check =
				static_cast<std::size_t>(tags.front().second) == c->startRef().tag()
			 && static_cast<std::size_t>(tags.back().second) == c->endRef().tag();
	}

	return check;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace test
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
