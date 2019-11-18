/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Translate class basic functionality.

\*---------------------------------------------------------------------------*/

#include "Axis.h"
#include "Point.h"
#include "Translate.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	geometry::Translate translator;

	// test parameter setting
	
	// should be unset
	test::compareTest
	(
		pass,
		!translator.isSet(),
		output,
		"Checking if unset"
	);

	// set vector
	geometry::Vector v {0, 1};
	translator.setParameters(v);

	// should be set
	test::compareTest
	(
		pass,
		translator.isSet(),
		output,
		"Checking if set"
	);

	// test manipulation
	geometry::Point p {0, 0};
	test::updateAndWait(1, output);

	translator.manipulate(p);
	test::updateAndWait(1, output);

	PointCoordinates coordinates {p.getCoordinates()};

	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 0.0) &&
			isEqual(coordinates[geometry::Axis::Y], 1.0) &&
			isEqual(coordinates[geometry::Axis::Z], 0.0)
		),
		output,
		"Checking point coordinates"
	);

	// set vector from points
	translator.setParameters
	(
		p,
		geometry::Point {1, 0}
	);

	translator.manipulate(p);
	test::updateAndWait(1, output);

	coordinates = p.getCoordinates();

	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 1.0) &&
			isEqual(coordinates[geometry::Axis::Y], 0.0) &&
			isEqual(coordinates[geometry::Axis::Z], 0.0)
		),
		output,
		"Checking point coordinates"
	);

	// set vector from point,
	// i.e. move to origin
	translator.setParameters(p);

	translator.manipulate(p);
	test::updateAndWait(1, output);

	coordinates = p.getCoordinates();

	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 0.0) &&
			isEqual(coordinates[geometry::Axis::Y], 0.0) &&
			isEqual(coordinates[geometry::Axis::Z], 0.0)
		),
		output,
		"Checking point coordinates"
	);

	// we should only have 1 point
	test::compareTest
	(
		pass,
		(test::getNumberOfEntities() == 1),
		output,
		"Checking number of entities"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
	
	test::finalize(output);
}

