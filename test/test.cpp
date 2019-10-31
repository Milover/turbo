/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
	Description:

	Testing Point class basic funtionality:
		- initialization
		- destruction
		- copying
		- member functions

	Testing Line class basic funtionality:
		- initialization
		- destruction
		- copying
		- member functions

\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <thread>
#include <type_traits>
#include <utility>

#include "gmsh.h"

#include "Axis.h"
#include <Line.h>
#include "Point.h"
#include "Utility.h"

namespace t = turbo;
namespace tg = turbo::geometry;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void initialize(std::string s)
{
	gmsh::initialize();
	gmsh::fltk::initialize();
	gmsh::option::setNumber("General.Terminal", 1);
	gmsh::model::add(s);
}


void update()
{
	gmsh::model::occ::synchronize();
	gmsh::fltk::update();
	gmsh::graphics::draw();
}


void finalize()
{
	update();
	gmsh::fltk::run();
	gmsh::finalize();
}


void updateAndWait(const int d)
{
	update();

    std::chrono::seconds time(d);
    std::this_thread::sleep_for(time);
}


template<typename... Args>
void echo(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}


void listEntities()
{
	t::Vectorpair<int> v;
	gmsh::model::getEntities(v);

	for (auto p : v)
	{
		echo ("entity dimTag: ", p.first, ' ', p.second);
	}
}


int getNumberOfEntities()
{
	t::Vectorpair<int> v;
	gmsh::model::getEntities(v);

	return v.size();
}


void testResult(std::string s, bool pass)
{
	std::cout << s;

	int width {50};
	width -= s.size();

	if (pass)
		std::cout << std::setw(width) << "PASS\n";
	else
		std::cout << std::setw(width) << "FAIL\n";
}


template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almostEqual(T x, T y, int ulp = 2)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::abs(x-y) < std::numeric_limits<T>::min();
}


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

