/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing RegistryObject/LimitedValue class basic funtionality
	through the OutletVelocity class.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>

#include "General.h"
#include "InputRegistry.h"
#include "OutletVelocity.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	Vector v {1.0, 0.0};

	// try some constructors
	input::OutletVelocity tmp_1 {v};
	input::OutletVelocity tmp_2 {tmp_1};
	input::OutletVelocity tmp_3 {std::move(tmp_2)};
	input::OutletVelocity tmp_4
	{
		input::OutletVelocity {v}
	};
	tmp_2 = std::move(tmp_3);
	tmp_3 = tmp_4;

	// should be the values we've initialized with
	test::compareTest
	(
		pass,
		(
			tmp_1.value() == v
		 && tmp_2.value() == v
		 && tmp_3.value() == v
		 && tmp_4.value() == v
		),
		output,
		"Checking initialized value"
	);

	// try to construct/set with a bunch of stuff,
	// should catch everything invalid
	input::OutletVelocity tmp_set {v};
	int shouldBeCaught {0};
	int caught {0};

	for (int i {0}; i < 10; ++i)
		test::echo(test::randomInt(0, 1));

	for (int i {0}; i < 1000; ++i)
	{
		Vector value {v};

		// sometimes nan some one of the values
		if
		(
			bool(test::randomInt(0, 1))
		)
		{
			value[test::randomInt(0, 2)] = NAN;
			++shouldBeCaught;
		}

		try
		{
			input::OutletVelocity tmp {value};
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
	// should thros because
	// input has not yet been defined
	try
	{
		input::OutletVelocity c_2_tmp
		{
			input::read<input::OutletVelocity>()
		};
		pass = false;
	}
	catch(...)
	{
		pass = true ? pass == true : false;
	}

// TODO: mass-test parsing from input

	// read from input
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"OutletVelocity", "(1.0 0.0 0.0)"}
		}
	);

	input::OutletVelocity c_2 {input::read<input::OutletVelocity>()};

	test::compareTest
	(
		pass,
		c_2.value() == Vector {1.0, 0.0},
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
