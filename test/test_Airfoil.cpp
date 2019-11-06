/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	Description:

	Testing Point class basic funtionality:
		- initialization
		- destruction
		- copying
		- member functions

\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "gmsh.h"

#include "Axis.h"
#include "Line.h"
#include "Point.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;
namespace tg = geometry;
namespace tt = test;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main() {
	
	bool passPoint {true};
	bool passLine {true};
	bool passUtility {true};

	tt::initialize("test_2", false);

	// Test Point construction
	tg::Point p1 {0,0};		// construct from components
	tg::Point p2 {1,0};
	tg::Point p3 {p1};		// construct from Point

	tt::updateAndWait(1, false);

	// translating so we can construct Line
	gmsh::model::occ::translate
	(
		Vectorpair<int> {p3.getDimTag()},
		2,
		0,
		0
	);

	tt::updateAndWait(1, false);

	// Test Point member functions
	if
	(
		p1.getDimTag().first != 0 ||
		p2.getDimTag().first != 0 ||
		p3.getDimTag().first != 0
	)
	{
		passPoint = false;
		passUtility = false;
	}

	std::vector<double> coordinates;

	coordinates = p1.getCoordinates();

	if
	(
		coordinates.at(toUnderlying(Axis::X)) != 0 ||
		coordinates.at(toUnderlying(Axis::Y)) != 0 ||
		coordinates.at(toUnderlying(Axis::Z)) != 0
	)
	{
		passPoint = false;
		passUtility = false;
	}

	coordinates = p3.getCoordinates();

	if
	(
		coordinates.at(toUnderlying(Axis::X)) != 2 ||
		coordinates.at(toUnderlying(Axis::Y)) != 0 ||
		coordinates.at(toUnderlying(Axis::Z)) != 0
	)
	{
		passPoint = false;
		passUtility = false;
	}

	// Test Line construction
	tg::Line l1 {p1, p2};	// construct from Points
	tg::Line l2 {p2, p3};
	tg::Line l3 {l1};		// construct from Line

	tt::updateAndWait(1, false);

	// Test Line member functions
	if
	(
		l1.getDimTag().first != 1 ||
		l3.getDimTag().first != 1
	)
	{
		passLine = false;
		passUtility = false;
	}

	if
	(
		isEqual(l1.getLength(), 1.0) ||
		isEqual(l3.getLength(), 1.0)
	)
	{
		passLine = false;
		passUtility = false;
	}

	int numberOfEntities {tt::getNumberOfEntities()};

	// Test dependency manipulation
	gmsh::model::occ::translate
	(
		Vectorpair<int> {l3.getDimTag()},
		0,
		1,
		0
	);

	tt::updateAndWait(1, false);

	// should have the same entities as before translation
	if (numberOfEntities != tt::getNumberOfEntities())
	{
		passPoint = false;
		passLine = false;
		passUtility = false;
	}

	// test pass or fail
	if (passPoint)
		tt::echo("passPoint");
	if (passLine)
		tt::echo("passLine");
		

	tt::finalize(false);
}

