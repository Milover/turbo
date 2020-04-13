/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Naca4DigitModifiedDistribution class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "Naca4DigitModifiedDistribution.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// test construction
	Stringmap<> input_1
	{
		{"maxThickness", "0.5"},
	};
	Stringmap<> input_2
	{
		{"maxThickness", "0.5"},
		{"maxThicknessPosition", "0.5"},
		{"radiusIndex", "3"}
	};
	geometry::Naca4DigitModifiedDistribution distribution_1 {input_1};
	geometry::Naca4DigitModifiedDistribution temp {input_2};
	geometry::Naca4DigitModifiedDistribution distribution_2 {std::move(temp)};

	// test construction related stuff
	test::compareTest
	(
		pass,
		distribution_1.hasKey("maxThickness"),
		output,
		"Checking hasKey()"
	);
	test::compareTest
	(
		pass,
		distribution_1.hasValue("maxThickness"),
		output,
		"Checking hasValue()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_1.get("maxThickness"), 0.5
		),
		output,
		"Checking get()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_1.get("maxThicknessPosition"), 0.3
		),
		output,
		"Checking get()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_1.get("radiusIndex"), 6.0
		),
		output,
		"Checking get()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_2.get("maxThickness"), 0.5
		),
		output,
		"Checking get()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_2.get("maxThicknessPosition"), 0.5
		),
		output,
		"Checking get()"
	);
	test::compareTest
	(
		pass,
		isEqual
		(
			distribution_2.get("radiusIndex"), 3.0
		),
		output,
		"Checking get()"
	);


	// test
	double x;
	for (int i {0}; i < 100; i++)
	{
		x = static_cast<double>(i) / 100.0;

		if (output)
			std::cout << distribution_1.getThicknessAt(x) << '\n';
	}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
