/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing TranslateToPoint class basic functionality.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "Axis.h"
#include "Point.h"
#include "TranslateToPoint.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	geometry::TranslateToPoint translator;

	// test parameter setting
	
	// should be unset
	test::compareTest
	(
		pass,
		!translator.isSet(),
		output,
		"Checking if unset"
	);

	// set parameter
	geometry::Point pFrom {0, 0};
	geometry::Point pTo {1, 0};
	test::updateAndWait(1, output);

	translator.setParameters(pFrom, pTo);

	// should be set
	test::compareTest
	(
		pass,
		translator.isSet(),
		output,
		"Checking if set"
	);

	// test manipulation
	geometry::Point p1 {0, 0};
	test::updateAndWait(1, output);

	translator.manipulate
	(
		Vectorpair<int> {p1.getDimTag()}
	);
	test::updateAndWait(1, output);

	// p1 should have been translated
	std::vector<double> coordinates {p1.getCoordinates()};

	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[toUnderlying(Axis::X)], 1.0) &&
			isEqual(coordinates[toUnderlying(Axis::Y)], 0.0) &&
			isEqual(coordinates[toUnderlying(Axis::Z)], 0.0)
		),
		output,
		"Checking point coordinates"
	);

	// we should only have 1 point
	test::compareTest
	(
		pass,
		(test::getNumberOfEntities() == 3),
		output,
		"Checking number of entities"
	);

	// vector should still be set
	geometry::Point p2 {1, 0};
	test::updateAndWait(1, output);

	translator.manipulate
	(
		Vectorpair<int> {p2.getDimTag()}
	);
	test::updateAndWait(1, output);

	// p2 should have been translated
	coordinates = p2.getCoordinates();

	test::compareTest
	(
		pass,
		(
			isEqual(coordinates[toUnderlying(Axis::X)], 2.0) &&
			isEqual(coordinates[toUnderlying(Axis::Y)], 0.0) &&
			isEqual(coordinates[toUnderlying(Axis::Z)], 0.0)
		),
		output,
		"Checking point coordinates"
	);

	// we should only have 2 points
	test::compareTest
	(
		pass,
		(test::getNumberOfEntities() == 4),
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

