/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing ProfileGeneratorInterface basic functionality.

\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include <string>
#include <vector>

#include "Point.h"
#include "ProfileGeneratorInterface.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	// initialization test
	Stringmap input_1 {};
	Stringmap input_2
	{
		{"buildFrom", "garbage"}
	};
	Stringmap input
	{
		{"buildFrom", "naca"},
		{"series", "4412"}
	};
	try
	{
		geometry::ProfileGeneratorInterface interface_1 {input_1};
	}
	catch (std::runtime_error& e)
	{}

	try
	{
		geometry::ProfileGeneratorInterface interface_2 {input_2};
	}
	catch (std::invalid_argument& e)
	{}
	
	geometry::ProfileGeneratorInterface interface {input};

	// check if empty
	test::compareTest
	(
		pass,
		!interface.isEmpty(),
		output,
		"Checking if empty"
	);
	
	// check size
	test::compareTest
	(
		pass,
		(
			interface.getSize() == 40
		),
		output,
		"Checking size"
	);

	// build geometry
	std::vector<geometry::Point> upperPoints;
	std::vector<geometry::Point> lowerPoints;

	for (int i {0}; i < interface.getSize(); i++)
	{
		upperPoints.push_back(interface.getUpperPointAt(i));
		lowerPoints.push_back(interface.getLowerPointAt(i));
	}

	test::updateAndWait(1, output);

	// check if we've built everything
	test::compareTest
	(
		pass,
		(
			test::getNumberOfEntities() == 2 * interface.getSize()
		),
		output,
		"Checking entities"
	);
	

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
	
	test::finalize(output);
}

