/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing BezierCurve class basic funtionality.

\*---------------------------------------------------------------------------*/

#include "BezierCurve.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	[[maybe_unused]] bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	std::vector<Vector> points
	{
		{0.0, 0.0},
		{1.0, 1.0},
		{2.0, 0.0}
	};

	math::BezierCurve<1> bc_1 {points[0], points[2]};
	math::BezierCurve<2> bc_2 {points[0], points[1], points[2]};

	// testing values of 1st order b-curve
	test::compareTest
	(
		pass,
		(
			bc_1(0.0) == points[0]
		 && bc_1(0.5) == Vector {1.0, 0.0}
		 && bc_1(1.0) == points[2]
		),
		output,
		"Checking B<1>(t)"
	);

	// testing values of 2nd order b-curve
	test::compareTest
	(
		pass,
		(
			bc_2(0.0) == points[0]
		 && bc_2(0.5) == Vector {1.0, 0.5}
		 && bc_2(1.0) == points[2]
		),
		output,
		"Checking B<2>(t)"
	);


	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
