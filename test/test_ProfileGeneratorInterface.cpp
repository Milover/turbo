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

namespace t = turbo;
namespace tg = turbo::geometry;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main() {
	
	bool passPoint {true};
	bool passLine {true};
	bool passUtility {true};

	initialize("test_2");

	// Test Point construction
	tg::Point p1 {0,0};		// construct from components
	tg::Point p2 {1,0};
	tg::Point p3 {p1};		// construct from Point

	updateAndWait(1);

	// translating so we can construct Line
	gmsh::model::occ::translate
	(
		t::Vectorpair<int> {p3.getDimTag()},
		2,
		0,
		0
	);

	updateAndWait(1);

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
		coordinates.at(t::toUnderlying(t::Axis::X)) != 0 ||
		coordinates.at(t::toUnderlying(t::Axis::Y)) != 0 ||
		coordinates.at(t::toUnderlying(t::Axis::Z)) != 0
	)
	{
		passPoint = false;
		passUtility = false;
	}

	coordinates = p3.getCoordinates();

	if
	(
		coordinates.at(t::toUnderlying(t::Axis::X)) != 2 ||
		coordinates.at(t::toUnderlying(t::Axis::Y)) != 0 ||
		coordinates.at(t::toUnderlying(t::Axis::Z)) != 0
	)
	{
		passPoint = false;
		passUtility = false;
	}

	// Test Line construction
	tg::Line l1 {p1, p2};	// construct from Points
	tg::Line l2 {p2, p3};
	tg::Line l3 {l1};		// construct from Line

	updateAndWait(1);

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
		almostEqual(l1.getLength(), 1.0) ||
		almostEqual(l3.getLength(), 1.0)
	)
	{
		passLine = false;
		passUtility = false;
	}

	int numberOfEntities {getNumberOfEntities()};

	// Test dependency manipulation
	gmsh::model::occ::translate
	(
		t::Vectorpair<int> {l3.getDimTag()},
		0,
		1,
		0
	);

	updateAndWait(1);

	// should have the same entities as before translation
	if (numberOfEntities != getNumberOfEntities())
	{
		passPoint = false;
		passLine = false;
		passUtility = false;
	}

	// test pass or fail
	echo("Test 1:");

	testResult("turbo::geometry::Point", passPoint);
	testResult("turbo::geometry::Line", passLine);
	testResult("turbo::Utility", passUtility);

	finalize();
}

