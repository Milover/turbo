/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing InputRegistry class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

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

	Map<String> table
	{
		{{"first"},		{"table"}},
		{{"second"},	{"table"}}
	};
	HashMap<String> hashtable
	{
		{{"first"},		{"hashtable"}},
		{{"second"},	{"hashtable"}}
	};

	// should be empty
	test::compareTest
	(
		pass,
		input::InputRegistry::empty(),
		output,
		"Checking if empty"
	);

	// test with map
	input::InputRegistry::store
	(
		std::move(table)
	);

	// should not be empty
	test::compareTest
	(
		pass,
		!input::InputRegistry::empty(),
		output,
		"Checking if not empty"
	);

	// should only have keys that were assigned
	test::compareTest
	(
		pass,
		(
			input::InputRegistry::has("first")
		 && input::InputRegistry::has("second")
		 && !input::InputRegistry::has("third")
		),
		output,
		"Checking keys"
	);

	// should get proper values back
	test::compareTest
	(
		pass,
		(
			input::InputRegistry::get("first") == "table"
		 && input::InputRegistry::get("second") == "table"
		),
		output,
		"Checking values"
	);


	// test with unordered_map
	input::InputRegistry::store
	(
		std::move(hashtable)
	);

	// should not be empty
	test::compareTest
	(
		pass,
		!input::InputRegistry::empty(),
		output,
		"Checking if not empty"
	);

	// should only have keys that were assigned
	test::compareTest
	(
		pass,
		(
			input::InputRegistry::has("first")
		 && input::InputRegistry::has("second")
		 && !input::InputRegistry::has("third")
		),
		output,
		"Checking keys"
	);

	// should get proper values back
	test::compareTest
	(
		pass,
		(
			input::InputRegistry::get("first") == "hashtable"
		 && input::InputRegistry::get("second") == "hashtable"
		),
		output,
		"Checking values"
	);

	// should except here
	try
	{
		input::InputRegistry::get("random_string");
		pass = false;
	}
	catch(...)
	{}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
