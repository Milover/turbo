/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Point class basic funtionality, along with some
	Shape class member functions.

\*---------------------------------------------------------------------------*/

#include "gmsh.h"

#include "General.h"
#include "Point.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	// Test Point construction
	geometry::Point p1 {0,0};	// construct from components
	geometry::Point p2 {p1};	// construct from Point
	geometry::Point p3			// construct from Vector (Coordinates)
	{
		Vector {0.0, 0.0}
	};

	test::updateAndWait(1, output);

	// try to modify
	gmsh::model::occ::translate
	(
		Vectorpair<Integer> {p2.dimTag()},
		2,
		0,
		0
	);

	test::updateAndWait(1, output);

	// Test Point member functions
	test::compareTest
	(
		pass,
		(
			p1.dimTag().first == 0 &&
			p2.dimTag().first == 0
		),
		output,
		"Checking dimension"
	);

	Vector coordinates;
	coordinates = p1.coordinates();
	test::compareTest
	(
		pass,
		(
			coordinates == Vector {0.0, 0.0}
		),
		output,
		"Checking coordinates"
	);

	coordinates = p2.coordinates();
	test::compareTest
	(
		pass,
		(
			coordinates == Vector {2.0, 0.0}
		),
		output,
		"Checking coordinates"
	);
	
	auto [min_1, max_1] {p1.boundingBox()};
	test::compareTest
	(
		pass,
		(
			min_1 == Vector {0.0, 0.0}
		),
		output,
		"Checking bounding box"
	);
	
	auto [min_2, max_2] {p2.boundingBox()};
	test::compareTest
	(
		pass,
		(
			min_2 == Vector {2.0, 0.0}
		),
		output,
		"Checking bounding box"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
