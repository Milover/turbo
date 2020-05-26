/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Line class basic funtionality and dependency behaviour
	of the Line class

\*---------------------------------------------------------------------------*/

#include <vector>

#include "Bezier.h"
#include "General.h"
#include "GmshControl.h"
#include "Line.h"
#include "Model.h"
#include "PlanarSurface.h"
#include "Point.h"
#include "Spline.h"
#include "Vector.h"

#include "Test.h"
#include "TestSurfaces.h"

using namespace turbo;
using Coordinates = Vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Line makeLine
(
	const Sptr<geometry::Point>& start,
	const Sptr<geometry::Point>& end
)
{
	return geometry::Line {start, end};
}


geometry::Spline makeSpline
(
	const Sptr<geometry::Point>& start,
	const Sptr<geometry::Point>& end
)
{
	return geometry::Spline
	{
		start,
		std::vector<Coordinates>
		{
			start->coordinates(),
			Coordinates {2.0, 2.0},
			end->coordinates()
		},
		end
	};
}


geometry::Bezier makeBezier
(
	const Sptr<geometry::Point>& start,
	const Sptr<geometry::Point>& end
)
{
	return geometry::Bezier
	{
		start,
		std::vector<Coordinates>
		{
			start->coordinates(),
			Coordinates {0.0, 2.0},
			end->coordinates()
		},
		end
	};
}


/*
geometry::Spline fromFunction()
{
	return geometry::Spline
	{
		std::vector<Coordinates>
		{
			Coordinates {0.0, 0.0},
			Coordinates {1.0, 1.0},
			Coordinates {2.0, 0.0}
		}
	};
}
*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	std::vector<Sptr<geometry::Point>> corners;

	corners.emplace_back
	(
		new geometry::Point {Coordinates {0.0, 0.0}}
	);
	corners.emplace_back
	(
		new geometry::Point {Coordinates {2.0, 0.0}}
	);
	corners.emplace_back
	(
		new geometry::Point {Coordinates {1.0, 1.0}}
	);

	Sptr<geometry::Curve> lineSptr
	{
		new geometry::Line
		{
			makeLine(corners[0], corners[1])
		}
	};
	Sptr<geometry::Curve> splineSptr
	{
		new geometry::Spline
		{
			makeSpline(corners[1], corners[2])
		}
	};
	Sptr<geometry::Curve> bezierSptr
	{
		new geometry::Bezier
		{
			makeBezier(corners[2], corners[0])
		}
	};

	// Test Line construction
	std::vector<Uptr<geometry::Surface>> surfaces;

	surfaces.emplace_back							// Curves&&...
	(
		new geometry::PlanarSurface
		{
			makeLine(corners[0], corners[1]),
			makeSpline(corners[1], corners[2]),
			makeBezier(corners[2], corners[0])
		}
	);
	surfaces.emplace_back							// const Sptr<Curves>&...
	(
		new geometry::PlanarSurface
		{
			lineSptr,
			splineSptr,
			bezierSptr
		}
	);
	surfaces.emplace_back							// Sptr<Curves>&&...
	(
		new geometry::PlanarSurface
		{
			std::move(lineSptr),
			std::move(splineSptr),
			std::move(bezierSptr)
		}
	);
	surfaces.emplace_back							// Sptr<Curves>&&...
	(
		new geometry::PlanarSurface
		{
			Sptr<geometry::Curve>
			{
				new geometry::Line
				{
					makeLine(corners[0], corners[1])
				}
			},
			Sptr<geometry::Curve>
			{
				new geometry::Spline
				{
					makeSpline(corners[1], corners[2])
				}
			},
			Sptr<geometry::Curve>
			{
				new geometry::Bezier
				{
					makeBezier(corners[2], corners[0])
				}
			}
		}
	);

	updateAndWait(1);

	Integer numberOfEntities {test::getNumberOfEntities()};

	// 3 points
	// 9 curves
	// 4 surfaces
	test::compareTest
	(
		pass,
		(numberOfEntities == 16),
		output,
		"Checking entitites (16)"
	);

	// check dimension
	test::compareTest
	(
		pass,
		test::checkSurfaceDimension(surfaces),
		output,
		"Checking dimensions"
	);

	// check curve tags
	test::compareTest
	(
		pass,
		test::checkSurfaceTags(surfaces),
		output,
		"Checking tags"
	);

	// check boundary curves
	test::compareTest
	(
		pass,
		test::checkSurfaceBoundary(surfaces),
		output,
		"Checking boundary curves"
	);

	// we've created 9 points (3 + 2 per surface (but 3 curves are shared))
	// (2 per line (1), 3 per curve (2), 3 are shared)
	test::compareTest
	(
		pass,
		geometry::Point::count() == 9,
		output,
		"Checking number of created points"
	);

	// we've created 9 curves (3 per surface, 3 are shared)
	test::compareTest
	(
		pass,
		geometry::Curve::count() == 9,
		output,
		"Checking number of created curves"
	);

	surfaces.clear();
	corners.clear();
	updateAndWait(1);

	// only the 3 curve-ptrs and 3 point-ptrs should be left
	test::compareTest
	(
		pass,
		test::getNumberOfEntities() == 6,
		output,
		"Checking cleared state"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
