/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Line class basic funtionality and dependency behaviour
	of the Line class

\*---------------------------------------------------------------------------*/

#include <vector>

#include "General.h"
#include "GmshControl.h"
#include "Spline.h"
#include "Model.h"
#include "Point.h"
#include "Vector.h"

#include "Test.h"
#include "TestCurves.h"

using namespace turbo;
using Coordinates = Vector;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

geometry::Spline fromFunction()
{
	return geometry::Spline
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
		Uptr<geometry::Spline>				// std::vector<Coordintes>&
		{
			new geometry::Spline {coords}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Point&&, std::vector<Coordintes>&, Point&&
		{
			new geometry::Spline
			{
				geometry::Point {coords.front()},
				coords,
				geometry::Point {coords.back()}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Point&&, std::vector<Coordintes>&
		{
			new geometry::Spline
			{
				geometry::Point {coords.front()},
				coords
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// std::vector<Coordintes>&, Point&&
		{
			new geometry::Spline
			{
				coords,
				geometry::Point {coords.back()}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Sptr<Point>&&, std::vector<Coordintes>&, Sptr<Point>&&
		{
			new geometry::Spline
			{
				Sptr<geometry::Point> {new geometry::Point {coords.front()}},
				coords,
				Sptr<geometry::Point> {new geometry::Point {coords.back()}}
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Sptr<Point>&&, std::vector<Coordintes>&
		{
			new geometry::Spline
			{
				Sptr<geometry::Point> {new geometry::Point {coords.front()}},
				coords
			}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// std::vector<Coordintes>&, Sptr<Point>&&
		{
			new geometry::Spline
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
		Uptr<geometry::Spline>				// Sptr<Point>&, std::vector<Coordintes>&, Sptr<Point>&
		{
			new geometry::Spline {sp1, coords, sp2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Sptr<Point>&, std::vector<Coordintes>&
		{
			new geometry::Spline {sp1, coords}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// std::vector<Coordintes>&, Sptr<Point>&
		{
			new geometry::Spline {coords, sp2}
		}
	);
	curves.push_back
	(
		Uptr<geometry::Spline>				// Spline&&
		{
			new geometry::Spline {fromFunction()}
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
