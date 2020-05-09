/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Point class basic funtionality, along with some
	Shape class member functions.

\*---------------------------------------------------------------------------*/

#include "GmshControl.h"
#include "Model.h"
#include "Point.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	geometry::Point::Coordinates c {1.0, 0.0};

	// Test Point construction
	geometry::Point p1 {0.0, 0.0};		// raw Floats
	geometry::Point p2 {c};				// Coordinates&
	geometry::Point p3					// Coordinates&&
	{
		geometry::Point::Coordinates {2.0, 0.0}
	};
	geometry::Point p4					// Point&&
	{
		geometry::Point {3.0, 0.0}
	};

	updateAndWait(1);

	// check dimension
	test::compareTest
	(
		pass,
		(
			p1.dim == 0
		 && p2.dim == 0
		 && p3.dim == 0
		 && p4.dim == 0
		),
		output,
		"Checking dimensions"
	);

	// check tags (we've only made 3 points)
	test::compareTest
	(
		pass,
		(
			p1.tag() == 1
		 && p2.tag() == 2
		 && p3.tag() == 3
		 && p4.tag() == 4
		),
		output,
		"Checking tags"
	);

	// check coordinates
	test::compareTest
	(
		pass,
		(
			p1.coordinates() == geometry::Point::Coordinates {0.0, 0.0}
		 && p2.coordinates() == geometry::Point::Coordinates {1.0, 0.0}
		 && p3.coordinates() == geometry::Point::Coordinates {2.0, 0.0}
		 && p4.coordinates() == geometry::Point::Coordinates {3.0, 0.0}
		),
		output,
		"Checking coordinates"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
