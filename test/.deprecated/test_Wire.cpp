/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Spline class basic funtionality and dependency behaviour
	of the Point class

	NOTE:
		This test is lacking because the curve loop behaves oddly and it is
		difficult to construct a worthwile test. Since they will exclusively
		be used to construct surfaces (and be expended in the process) only
		basic construction is tested (default/move).

	XXX:
		It will also always fail because the loop tag is always wrong
		(the constructor function returns a random tag of one of the curves
		used during construction) so when the destructor calls 'remove'
		the kernel throws an exception because the tag doesn't exist.

	TODO:
		Remove completely once surfaces are implemented.

\*---------------------------------------------------------------------------*/

#include "gmsh.h"

#include "Line.h"
#include "Loop.h"
#include "Point.h"
#include "Spline.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Loop fromList()
{
	geometry::Point p1 {0,0};
	geometry::Point p2 {1,0};

	geometry::Line line {p1, p2};
	geometry::Spline spline
	{
		std::vector<geometry::Point>
		{
			geometry::Point {1,0},
			geometry::Point {1,1},
			geometry::Point {0,1},
			geometry::Point {0,0}
		}
	};

	return geometry::Loop {line, spline};
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	// Test Line construction
	geometry::Loop loop			// construct from list (and move)
	{
		std::move(fromList())
	};

	test::updateAndWait(1, output);

	// 2 points per loop
	// 1 loop
	test::compareTest
	(
		pass,
		(test::getNumberOfEntities() == 3),
		output,
		"Checking entitites (3)"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
