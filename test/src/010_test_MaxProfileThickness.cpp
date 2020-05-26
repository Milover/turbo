/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing RegistryObject/LimitedValue class basic funtionality
	through the MaxCamberPosition class.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>

#include "General.h"
#include "InputRegistry.h"
#include "Utility.h"
#include "MaxCamberPosition.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// try some constructors
	input::MaxCamberPosition tmp_1 {};
	input::MaxCamberPosition tmp_2 {tmp_1};
	input::MaxCamberPosition tmp_3 {std::move(tmp_2)};
	input::MaxCamberPosition tmp_4
	{
		input::MaxCamberPosition {}
	};
	tmp_2 = std::move(tmp_3);
	tmp_3 = tmp_4;

	// should be default values
	test::compareTest
	(
		pass,
		(
			isEqual(tmp_1.value(), 0.4)
		 && isEqual(tmp_2.value(), 0.4)
		 && isEqual(tmp_3.value(), 0.4)
		 && isEqual(tmp_4.value(), 0.4)
		),
		output,
		"Checking default value"
	);

	// try to construct/set with a bunch of stuff,
	// should catch everything invalid
	double value;
	input::MaxCamberPosition tmp_set {};
	int shouldBeCaught {0};
	int caught {0};

	for (int i {0}; i < 1000; ++i)
	{
		value = 0.01 * static_cast<double>(test::randomInt(-500, 500));

		// nan sometimes
		if
		(
			bool(test::randomInt(0, 1))
		)
			value = NAN;

		if
		(
			std::isnan(value)
		 || !isInRange(value, 0.0, 1.0)
		)
			++shouldBeCaught;

		try
		{
			input::MaxCamberPosition tmp {value};
		}
		catch(...)
		{
			try
			{
				tmp_set.set(value);
			}
			catch(...)
			{
				++caught;
			}
		}
	}
	test::compareTest
	(
		pass,
		caught == shouldBeCaught,
		output,
		"Checking value limiting"
	);

	// try to read from input,
	// should default construct because
	// input has not yet been defined
	input::MaxCamberPosition vde
	{
		input::read<input::MaxCamberPosition>()
	};

	test::compareTest
	(
		pass,
		isEqual(vde.value(), 0.4),
		output,
		"Checking read() default construction"
	);

// TODO: mass-test parsing from input

	// read from input
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"MaxCamberPosition", "0.5"}
		}
	);

	vde = input::read<input::MaxCamberPosition>();

	test::compareTest
	(
		pass,
		isEqual(vde.value(), 0.5),
		output,
		"Checking basic read() functionality"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
