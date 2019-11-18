/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Rotate class basic functionality.

\*---------------------------------------------------------------------------*/

#include "Axis.h"
#include "Point.h"
#include "Scale.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	geometry::Scale scaler;

	// test parameter setting

	// should be unset
	test::compareTest
	(
		pass,
		!scaler.isSet(),
		output,
		"Checking if unset"
	);

	// set parameters
	geometry::Point origin {0.0, 0.0};
	scaler.setParameters(origin, 2, 2, 2);

	// should be set
	test::compareTest
	(
		pass,
		scaler.isSet(),
		output,
		"Checking if set"
	);

	// test manipulation
	geometry::Point p {1, 1, 1};
	test::updateAndWait(1, output);

	scaler.manipulate(p);
	test::updateAndWait(1, output);

	PointCoordinates coordinates {p.getCoordinates()};
	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 2.0) &&
			isEqual(coordinates[geometry::Axis::Y], 2.0) &&
			isEqual(coordinates[geometry::Axis::Z], 2.0)
		),
		output,
		"Checking point coordinates"
	);

	// set parameters for 2d uniform scale
	scaler.setParameters(origin, 0.5);

	scaler.manipulate(p);
	test::updateAndWait(1, output);

	coordinates = p.getCoordinates();
	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 1.0) &&
			isEqual(coordinates[geometry::Axis::Y], 1.0) &&
			isEqual(coordinates[geometry::Axis::Z], 2.0)
		),
		output,
		"Checking point coordinates"
	);

	// set parameters for 2d uniform scale about origin
	scaler.setParameters(2);

	scaler.manipulate(p);
	test::updateAndWait(1, output);

	coordinates = p.getCoordinates();
	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[geometry::Axis::X], 2.0) &&
			isEqual(coordinates[geometry::Axis::Y], 2.0) &&
			isEqual(coordinates[geometry::Axis::Z], 2.0)
		),
		output,
		"Checking point coordinates"
	);

	// we should only have 2 points (origin and p)
	test::compareTest
	(
		pass,
		(test::getNumberOfEntities() == 2),
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

