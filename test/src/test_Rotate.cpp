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
#include "Rotate.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	geometry::Rotate rotator;

	// test parameter setting

	// should be unset
	test::compareTest
	(
		pass,
		!rotator.isSet(),
		output,
		"Checking if unset"
	);

	// set parameters (default)
	double angle {0.5 * pi};
	rotator.setParameters(angle);

	// should be set
	test::compareTest
	(
		pass,
		rotator.isSet(),
		output,
		"Checking if set"
	);


	// lambda for comparisons
	auto compare = [](auto x, auto y)
	{
		return std::abs(x - y) < 1e-16;
	};

	// test manipulation
	geometry::Point p {1.0, 0.0};
	test::updateAndWait(1, output);

	rotator.manipulate(p);
	test::updateAndWait(1, output);

	// p1 should have been rotated
	PointCoordinates coordinates {p.getCoordinates()};

	test::compareTest
	(
		pass,
		(
			compare(coordinates[geometry::Axis::X], 0.0) &&
			compare(coordinates[geometry::Axis::Y], 1.0) &&
			compare(coordinates[geometry::Axis::Z], 0.0)
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

	// reset angle and try again
	angle = 0.5 * pi;
	rotator.setParameters
	(
		angle,
		geometry::Axis {geometry::XAxis {}}
	);

	rotator.manipulate(p);
	test::updateAndWait(1, output);

	coordinates = p.getCoordinates();

	test::compareTest
	(
		pass,
		(
			compare(coordinates[geometry::Axis::X], 0.0) &&
			compare(coordinates[geometry::Axis::Y], 0.0) &&
			compare(coordinates[geometry::Axis::Z], 1.0)
		),
		output,
		"Checking point coordinates"
	);

	// we should still only have 1 point
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

