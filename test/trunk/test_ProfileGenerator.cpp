/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing ProfileGenerator class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <iostream>
#include <utility>
#include <vector>

#include "gmsh.h"

#include "ProfileGenerator.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	// test construction

	InputRegistry::store
	(
		Stringmap<>
		{
			{"distribution", "naca4Digit"},
			{"maxThickness", "0.2"},
			{"camber", "naca2Digit"}
		}
	);

	"NEED_CONSTEXPR_TABLE_OF_POINTS_FOR_A_GIVEN_CAMBER"

	geometry::ConstantDistribution temp_1 {};
	geometry::ConstantDistribution temp_2 {temp_1};
	geometry::ConstantDistribution temp_3 {std::move(temp_1)};
	temp_3 = temp_2;
	temp_1 = std::move(temp_3);

	// test

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
