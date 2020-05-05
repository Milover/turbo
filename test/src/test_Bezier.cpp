/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Bezier class basic funtionality

\*---------------------------------------------------------------------------*/

#include <vector>

#include "General.h"
#include "GmshControl.h"
#include "Bezier.h"
#include "Model.h"
#include "Point.h"
#include "Vector.h"

#include "Test.h"
#include "TestCurves.h"

using namespace turbo;
using Coordinates = Vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Bezier fromFunction()
{
	return geometry::Bezier
	{
		std::vector<Coordinates>
		{
			Coordinates {0.0, 0.0},
			Coordinates {1.0, 1.0},
			Coordinates {2.0, 0.0}
		}
	};
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	std::vector<Coordinates> coords
	{
		Coordinates {0.0, 0.0},
		Coordinates {1.0, 1.0},
		Coordinates {2.0, 0.0}
	};

	// Test Line construction
	std::vector<Uptr<geometry::Curve>> curves;

	curves.push_back
	(
		Uptr<geometry::Bezier>				// std::vector<Coordintes>&
		{
			new geometry::Bezier {coords}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Point&&, std::vector<Coordintes>&, Point&&
		{
			new geometry::Bezier
			{
				geometry::Point {coords.front()},
				coords,
				geometry::Point {coords.back()}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Point&&, std::vector<Coordintes>&
		{
			new geometry::Bezier
			{
				geometry::Point {coords.front()},
				coords
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// std::vector<Coordintes>&, Point&&
		{
			new geometry::Bezier
			{
				coords,
				geometry::Point {coords.back()}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Sptr<Point>&&, std::vector<Coordintes>&, Sptr<Point>&&
		{
			new geometry::Bezier
			{
				Sptr<geometry::Point> {new geometry::Point {coords.front()}},
				coords,
				Sptr<geometry::Point> {new geometry::Point {coords.back()}}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Sptr<Point>&&, std::vector<Coordintes>&
		{
			new geometry::Bezier
			{
				Sptr<geometry::Point> {new geometry::Point {coords.front()}},
				coords
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// std::vector<Coordintes>&, Sptr<Point>&&
		{
			new geometry::Bezier
			{
				coords,
				Sptr<geometry::Point> {new geometry::Point {coords.back()}}
			}
		}
	);
	Sptr<geometry::Point> sp1 {new geometry::Point {coords.front()}};
	Sptr<geometry::Point> sp2 {new geometry::Point {coords.back()}};
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Sptr<Point>&, std::vector<Coordintes>&, Sptr<Point>&
		{
			new geometry::Bezier {sp1, coords, sp2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Sptr<Point>&, std::vector<Coordintes>&
		{
			new geometry::Bezier {sp1, coords}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// std::vector<Coordintes>&, Sptr<Point>&
		{
			new geometry::Bezier {coords, sp2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Bezier>				// Bezier&&
		{
			new geometry::Bezier {fromFunction()}
		}
	);

	updateAndWait(1);

	Integer numberOfEntities {test::getNumberOfEntities()};

	// 2 points per curve, 2 are shared between 3 curves (20),
	// 11 curves
	test::compareTest
	(
		pass,
		(numberOfEntities == 31),
		output,
		"Checking entitites (31)"
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

	// we've created 31 points (3 per curve, 2 are shared)
	test::compareTest
	(
		pass,
		geometry::Point::count() == 31,
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
