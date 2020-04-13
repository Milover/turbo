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
#include "General.h"
#include "InputRegistry.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// test construction
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"MaxProfileThickness", "0.5"}
		}
	);

	design::ConstantDistribution temp_1 {};
	design::ConstantDistribution temp_2 {temp_1};
	design::ConstantDistribution temp_3 {std::move(temp_1)};
	temp_3 = temp_2;
	temp_1 = std::move(temp_3);

	test::echo(isGreaterOrEqual(-1.0, 0.0));
	test::echo(isLessOrEqual(-1.0, 1.0));

	test::echo("here");

	test::echo(isInRange(-1.0, 0.0, 1.0));

	test::echo("here_2");

	// test
	Float x;
	int shouldBeCaught {0};
	for (int i {-100}; i < 100; ++i)
	{
		x = 0.01 * static_cast<Float>(i);

		try
		{
			// checking thickness
			if
			(
				!isEqual(temp_1.thickness(x), 0.25)
			 || !isEqual(temp_2.thickness(x), 0.25)
			)
				pass = false;
		}
		catch(...)
		{
			++shouldBeCaught;
		}
	}

	test::echo(shouldBeCaught);

	test::compareTest
	(
		pass,
		(shouldBeCaught == 100),
		output,
		"Checking thrown exceptions"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
