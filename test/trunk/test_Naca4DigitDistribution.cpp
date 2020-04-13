/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Naca4DigitDistribution class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "General.h"
#include "InputRegistry.h"
#include "Naca4DigitDistribution.h"
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
			{"maxThickness", "0.5"}
		}
	);

	geometry::Naca4DigitDistribution temp_1 {};
	geometry::Naca4DigitDistribution temp_2 {temp_1};
	geometry::Naca4DigitDistribution temp_3 {std::move(temp_1)};
	temp_3 = temp_2;
	temp_1 = std::move(temp_3);

	// test
	Float x;
	auto shouldBeCought {0};
	for (auto i {-100}; i < 100; ++i)
	{
		x = 0.01 * static_cast<Float>(i);

		try
			// checking thickness
			if
			(
				!isEqual(temp_1.thickness(x), "NEED_CONSTEXPR_TABLE_OF_POINTS")
			 || !isEqual(temp_2.thickness(x), "NEED_CONSTEXPR_TABLE_OF_POINTS")
			)
				pass = false;
		catch(...)
			++shouldBeCought;
	}

	test::compareTest
	(
		pass,
		(shouldBeCought == 100),
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
