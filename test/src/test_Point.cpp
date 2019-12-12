/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Point class basic funtionality, along with some
	Shape class member functions.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "gmsh.h"

#include "Axis.h"
#include "Point.h"
#include "Utility.h"

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

	test::updateAndWait(1, output);

	// try to modify
	gmsh::model::occ::translate
	(
		Vectorpair<int> {p2.getDimTag()},
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
			p1.getDimTag().first == 0 &&
			p2.getDimTag().first == 0
		),
		output,
		"Checking dimension"
	);

	PointCoordinates coordinates;
	coordinates = p1.getCoordinates();
	test::compareTest
	(
		pass,
		(
			coordinates.at(geometry::Axis::X) == 0 &&
			coordinates.at(geometry::Axis::Y) == 0 &&
			coordinates.at(geometry::Axis::Z) == 0
		),
		output,
		"Checking coordinates"
	);

	coordinates = p2.getCoordinates();
	test::compareTest
	(
		pass,
		(
			coordinates.at(geometry::Axis::X) == 2 &&
			coordinates.at(geometry::Axis::Y) == 0 &&
			coordinates.at(geometry::Axis::Z) == 0
		),
		output,
		"Checking coordinates"
	);
	
	Vectorpair<double> pBox {p1.getBoundingBox()};
	test::compareTest
	(
		pass,
		(
			isEqual(pBox[0].first, 0.0) &&
			isEqual(pBox[1].first, 0.0) &&
			isEqual(pBox[2].first, 0.0)
		),
		output,
		"Checking bounding box"
	);
	
	pBox = p2.getBoundingBox();
	test::compareTest
	(
		pass,
		(
			isEqual(pBox[0].first, 2.0) &&
			isEqual(pBox[1].first, 0.0) &&
			isEqual(pBox[2].first, 0.0)
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
