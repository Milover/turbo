/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Axis class basic funtionality.

\*---------------------------------------------------------------------------*/

#include "Axis.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", false);
	bool pass {true};

	// test construction

	// default constructor
	geometry::Axis a1
	{
		0, 0, 0,
		{1, 0, 0}
	};

	// copy constructor
	geometry::Axis a2 {a1};

	geometry::Axis a3 {geometry::ZAxis {}};

	// should be equal
	test::compareTest
	(
		pass,
		(a1 == a2),
		output,
		"Checking if equal"
	);

	test::compareTest
	(
		pass,
		(a3 == geometry::ZAxis {}),
		output,
		"Checking if equal"
	);

	// should not be equal
	test::compareTest
	(
		pass,
		(a1 != a3),
		output,
		"Checking if not equal"
	);

	// test member functions
	
	PointCoordinates p {0, 0, 0};
	geometry::Vector v {0, 0, 1};
	
	// should be equal
	test::compareTest
	(
		pass,
		(p == a3.getPointCoordinates()),
		output,
		"Checking point"
	);

	// should be equal
	test::compareTest
	(
		pass,
		(v == a3.getVector()),
		output,
		"Checking vector"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
