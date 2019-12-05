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

#include "Spline.h"
#include "Point.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Spline fromList()
{
	geometry::Point p1 {0,0};
	geometry::Point p2 {1,1};
	geometry::Point p3 {2,1};
	geometry::Point p4 {3,0};

	return geometry::Spline {p1, p2, p3, p4};
}


geometry::Spline fromVector()
{
	geometry::Point p1 {0,0};
	geometry::Point p2 {1,1};
	geometry::Point p3 {2,1};
	geometry::Point p4 {3,0};
	std::vector<geometry::Point> points {p1, p2, p3, p4};

	return geometry::Spline {points};
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {
	
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};


	// Test Line construction
	geometry::Spline s1 {fromList()};		// construct from points
	geometry::Spline s2 {fromVector()};				// construct from spline
	geometry::Spline s3
	{
		geometry::Point {0, 0},
		geometry::Point {1, 1},
		geometry::Point {2, 1},
		geometry::Point {3, 0}
	};
	geometry::Spline s4 {s3};

	test::updateAndWait(1, output);

	// Test Line member functions
	int numberOfEntities {test::getNumberOfEntities()};

	// Test dependency manipulation
	gmsh::model::geo::translate
	(
		Vectorpair<int> {s1.getDimTag()},
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

	test::listEntities();

	gmsh::model::geo::remove
	(
		Vectorpair<int>
		{
			s1.getDimTag(),
			s2.getDimTag(),
			s3.getDimTag(),
			s4.getDimTag()
		},
		true
	);
	test::updateAndWait(1, output);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
