/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing ConstantThickness class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "ConstantThickness.h"
#include "General.h"
#include "InputRegistry.h"
#include "Registry.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"

	// test construction
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"MaxProfileThickness", "0.5"}
		}
	);
	// a dummy registry so we can read the values
	input::Registry reg {};

	design::ConstantThickness temp_1 {reg};
	design::ConstantThickness temp_2 {std::move(temp_1)};
	design::ConstantThickness temp_3 {reg};
	temp_3 = std::move(temp_2);

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
				!isEqual(temp_3.thickness(x), 0.25)
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
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
