/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Spline class basic funtionality and dependency behaviour
	of the Point class

\*---------------------------------------------------------------------------*/

#include "gmsh.h"

#include "General.h"
#include "Point.h"
#include "Spline.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Spline fromVector()
{
	std::vector<geometry::Point> points
	{
		geometry::Point {0,0},
		geometry::Point {1,1},
		geometry::Point {2,1},
		geometry::Point {3,0}
	};

	return geometry::Spline {points};
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {
	
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	std::vector<geometry::Point> points
	{
		geometry::Point {0,0},
		geometry::Point {1,1},
		geometry::Point {2,1},
		geometry::Point {3,0}
	};

	// Test Line construction
	geometry::Spline s1 {points};			// construct from spline
	geometry::Spline s2 {fromVector()};		// construct from spline

	test::updateAndWait(1, output);

	int numberOfEntities {test::getNumberOfEntities()};

	// 4 raw points,
	// 2 points per spline (4),
	// 2 splines
	test::compareTest
	(
		pass,
		(numberOfEntities == 10),
		output,
		"Checking entitites (10)"
	);

	// Test dependency manipulation
	gmsh::model::occ::translate
	(
		Vectorpair<int> {s1.dimTag()},
		0,
		1,
		0
	);

	test::updateAndWait(1, output);

	// should have the same entities as before translation
	test::compareTest
	(
		pass,
		(numberOfEntities == test::getNumberOfEntities()),
		output,
		"Checking entitites"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
