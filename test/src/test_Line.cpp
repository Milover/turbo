/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Line class basic funtionality and dependency behaviour
	of the Line class

\*---------------------------------------------------------------------------*/

#include "General.h"
#include "GmshControl.h"
#include "Line.h"
#include "Model.h"
#include "Point.h"

#include "Test.h"
#include "TestCurves.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Line fromFunction()
{
	return geometry::Line
	{
		geometry::Point {0.0, 0.0},
		geometry::Point {1.0, 0.0}
	};
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	geometry::Point::Coordinates c1 {0.0, 0.0};
	geometry::Point::Coordinates c2 {1.0, 0.0};

	// Test Line construction
	std::vector<Uptr<geometry::Curve>> curves;

	curves.push_back
	(
		Uptr<geometry::Line>				// Coordinates&
		{
			new geometry::Line {c1, c2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Line>				// Coordinates&&
		{
			new geometry::Line
			{
				geometry::Point::Coordinates {0.0, 0.0},
				geometry::Point::Coordinates {1.0, 0.0}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Line>				// Point&&
		{
			new geometry::Line
			{
				geometry::Point {c1},
				geometry::Point {c2}
			}
		}
	);
	Sptr<geometry::Point> sp1 {new geometry::Point {c1}};
	Sptr<geometry::Point> sp2 {new geometry::Point {c2}};
	curves.push_back
	(
		Uptr<geometry::Line>				// Sptr<Point>&
		{
			new geometry::Line {sp1, sp2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Line>				// Sptr<Point>&&
		{
			new geometry::Line
			{
				Sptr<geometry::Point> {new geometry::Point {0.0, 0.0}},
				Sptr<geometry::Point> {new geometry::Point {1.0, 0.0}}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Line>				// Line&&
		{
			new geometry::Line {fromFunction()}
		}
	);

	updateAndWait(1);

	Integer numberOfEntities {test::getNumberOfEntities()};

	// 2 points per line (12),
	// 6 curves
	test::compareTest
	(
		pass,
		(numberOfEntities == 18),
		output,
		"Checking entitites (18)"
	);

	// check dimension
	test::compareTest
	(
		pass,
		test::checkCurveDimension(curves),
		output,
		"Checking dimensions"
	);

	// check curve tags
	test::compareTest
	(
		pass,
		test::checkCurveTags(curves),
		output,
		"Checking tags"
	);

	// check boundary points
	test::compareTest
	(
		pass,
		test::checkCurveBoundary(curves),
		output,
		"Checking start/end points"
	);

	// we've created 12 points
	test::compareTest
	(
		pass,
		geometry::Point::count() == 12,
		output,
		"Checking number of created points"
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
