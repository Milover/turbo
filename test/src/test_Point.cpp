/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Point class basic funtionality, along with some
	Shape class member functions.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "gmsh.h"

#include "Axis.h"
#include "Point.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {

	bool gui {test::parseCommandLineArgs(argc, argv)};
		
	test::initialize("test", gui);

	bool pass {true};

	// Test Point construction
	geometry::Point p1 {0,0};	// construct from components
	geometry::Point p2 {p1};	// construct from Point

	test::updateAndWait(1, gui);

	// try to modify
	gmsh::model::geo::translate
	(
		Vectorpair<int> {p2.getDimTag()},
		2,
		0,
		0
	);

	test::updateAndWait(1, gui);

	// Test Point member functions
	if
	(
		p1.getDimTag().first != 0 ||
		p2.getDimTag().first != 0
	)
		pass = false;

	std::vector<double> coordinates;
	coordinates = p1.getCoordinates();
	if
	(
		coordinates.at(toUnderlying(Axis::X)) != 0 ||
		coordinates.at(toUnderlying(Axis::Y)) != 0 ||
		coordinates.at(toUnderlying(Axis::Z)) != 0
	)
		pass = false;

	coordinates = p2.getCoordinates();
	if
	(
		coordinates.at(toUnderlying(Axis::X)) != 2 ||
		coordinates.at(toUnderlying(Axis::Y)) != 0 ||
		coordinates.at(toUnderlying(Axis::Z)) != 0
	)
		pass = false;
	
	Vectorpair<int> boundary;

	p1.getBoundary(boundary);
	if (!boundary.empty())
		pass = false;
	
	boundary.clear();

	p2.getBoundary(boundary);
	if (!boundary.empty())
		pass = false;
	
	Vectorpair<double> p1Box {p1.getBoundingBox()};
	if
	(
		!isEqual(p1Box[0].first, 0.0) ||
		!isEqual(p1Box[1].first, 0.0) ||
		!isEqual(p1Box[2].first, 0.0)
	)
		pass = false;
	
	Vectorpair<double> p2Box {p2.getBoundingBox()};
	if
	(
		!isEqual(p2Box[0].first, 2.0) ||
		!isEqual(p2Box[1].first, 0.0) ||
		!isEqual(p2Box[2].first, 0.0)
	)
		pass = false;
	
	if (p1.getName() != "")
		pass = false;

	if (p2.getName() != "")
		pass = false;
	
	p1.setName("p1");
	if (p1.getName() != "p1")
		pass = false;

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(gui);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
