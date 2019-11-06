/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Line class basic funtionality and dependency behaviour
	of the Point class

\*---------------------------------------------------------------------------*/

#include "gmsh.h"

#include "Line.h"
#include "Point.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {
	
	bool gui {test::parseCommandLineArgs(argc, argv)};

	test::initialize("test", gui);

	bool pass {true};

	// Test Point construction
	geometry::Point p1 {0,0};		// construct from components
	geometry::Point p2 {1,0};
	geometry::Point p3 {2,0};		// construct from Point

	test::updateAndWait(1, gui);

	// Test Line construction
	geometry::Line l1 {p1, p2};		// construct from Points
	geometry::Line l2 {p2, p3};
	geometry::Line l3 {l1};			// construct from Line

	test::updateAndWait(1, gui);

	// Test Line member functions
	if
	(
		l1.getDimTag().first != 1 ||
		l2.getDimTag().first != 1 ||
		l3.getDimTag().first != 1
	)
		pass = false;

	if
	(
		!isEqual(l1.getLength(), 1.0) ||
		!isEqual(l2.getLength(), 1.0) ||
		!isEqual(l3.getLength(), 1.0)
	)
		pass = false;

	int numberOfEntities {test::getNumberOfEntities()};

	// Test dependency manipulation
	gmsh::model::geo::translate
	(
		Vectorpair<int> {l3.getDimTag()},
		0,
		1,
		0
	);

	test::updateAndWait(1, gui);

	// should have the same entities as before translation
	if (numberOfEntities != test::getNumberOfEntities())
		pass = false;

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(gui);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
