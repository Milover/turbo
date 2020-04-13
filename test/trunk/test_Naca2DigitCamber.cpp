/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Naca2DigitCamber class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <iostream>
#include <utility>
#include <vector>

#include "General.h"
#include "InputRegistry.h"
#include "Naca2DigitCamber.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// test construction
	InputRegistry::store
	(
		Stringmap<>
		{
			{"camberPoints", "100"},
			{"spacing", "linear"},
			{"maxCamberPosition", "0.5"}
		}
	);

	geometry::Naca2DigitCamber temp_1 {};
	geometry::Naca2DigitCamber temp_2 {temp_1};
	geometry::Naca2DigitCamber temp_3 {std::move(temp_1)};
	temp_3 = temp_2;
	temp_1 = std::move(temp_3);

	// test

	"NEED_CONSTEXPR_TABLE_OF_POINTS_FOR_A_GIVEN_CAMBER"

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
