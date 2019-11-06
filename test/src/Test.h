/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Definitions of some utility functions used in unit tests

\*---------------------------------------------------------------------------*/

#ifndef TEST_H
#define TEST_H

#include <chrono>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

#include "gmsh.h"

#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace test
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void initialize
(
	std::string s,
	const bool gui = true
)
{
	if (gui)
	{
		gmsh::initialize();
		gmsh::fltk::initialize();
		gmsh::option::setNumber("General.Terminal", 1);
		gmsh::option::setNumber("General.Verbosity", 1000);
	}
	else
	{
		gmsh::initialize(0, 0, false);
	}
	gmsh::model::add(s);
}


void update(const bool gui)
{
	gmsh::model::geo::synchronize();

	if (gui)
	{
		gmsh::fltk::update();
		gmsh::graphics::draw();
	}
}


void finalize(const bool gui)
{
	update(gui);

	if (gui)
	{
		gmsh::fltk::run();
		gmsh::finalize();
	}
}


void updateAndWait
(
	const int d,
	const bool gui
)
{
	update(gui);

	if (gui)
	{
		std::chrono::seconds time(d);
		std::this_thread::sleep_for(time);
	}
}


template<typename... Args>
void echo(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}


void listEntities()
{
	turbo::Vectorpair<int> v;
	gmsh::model::getEntities(v);

	for (auto p : v)
	{
		echo ("entity dimTag: ", p.first, ' ', p.second);
	}
}


int getNumberOfEntities()
{
	turbo::Vectorpair<int> v;
	gmsh::model::getEntities(v);

	return v.size();
}

bool parseCommandLineArgs
(
	int argc,
	char* argv[]
)
{
	if
	(
		argc > 1 &&
		(std::strcmp(argv[1], "--no-gui")) == 0
	)
		return false;

	return true;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace test
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
