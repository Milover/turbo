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
#include "SolidityDistribution.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// try some constructors
	input::SolidityDistribution tmp_1 {};
	input::SolidityDistribution tmp_2 {tmp_1};
	input::SolidityDistribution tmp_3 {std::move(tmp_2)};
	input::SolidityDistribution tmp_4
	{
		input::SolidityDistribution {}
	};
	tmp_2 = std::move(tmp_3);
	tmp_3 = tmp_4;

	// should be default values
	test::compareTest
	(
		pass,
		(
			tmp_1.value().pointsCRef() == List<Float> {1.0}
		 && tmp_2.value().pointsCRef() == List<Float> {1.0}
		 && tmp_3.value().pointsCRef() == List<Float> {1.0}
		 && tmp_4.value().pointsCRef() == List<Float> {1.0}
		),
		output,
		"Checking default values"
	);

	// test interpolation

	// try to read from input,
	// should default construct because
	// input has not yet been defined
	input::SolidityDistribution sd
	{
		input::read<input::SolidityDistribution>()
	};

	test::compareTest
	(
		pass,
		sd.value().pointsCRef() == List<Float> {1.0},
		output,
		"Checking read() default construction"
	);

// TODO: mass-test parsing from input

	// read from input
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"SolidityDistribution", "(1.0 0.5 0.25)"}
		}
	);

	sd = input::read<input::SolidityDistribution>();

sd.print(std::cerr);

	test::compareTest
	(
		pass,
		sd.value().pointsCRef() == List<Float> {1.0, 0.5, 0.25},
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
