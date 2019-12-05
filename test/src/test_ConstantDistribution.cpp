/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing ConstantDistribution class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "ConstantDistribution.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// test construction
	Stringmap<> input
	{
		{"maxThickness", "0.5"},
	};
	geometry::ConstantDistribution temp {input};
	geometry::ConstantDistribution distribution {std::move(temp)};

	// test construction related stuff
	test::compareTest
	(
		pass,
		distribution.hasKey("maxThickness"),
		output,
		"Checking hasKey()"
	);
	test::compareTest
	(
		pass,
		distribution.hasValue("maxThickness"),
		output,
		"Checking hasValue()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution.get("maxThickness"), 0.5
		),
		output,
		"Checking get()"
	);

	// test
	double x;
	for (int i {0}; i < 100; i++)
	{
		x = static_cast<double>(i) / 100.0;

		// checking thickness
		if
		(
			!isEqual(distribution.getThicknessAt(x), 0.25)
		)
			pass = false;
	}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
