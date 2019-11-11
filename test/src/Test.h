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
#include <random>
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
	gmsh::option::setNumber("Geometry.AutoCoherence", 0);
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
		(std::strcmp(argv[1], "--result-only")) == 0
	)
		return false;

	return true;
}


int randomInt
(
	int min,
	int max
)
{
    std::random_device randomDevice;
    std::mt19937 generator {randomDevice()};
    std::uniform_int_distribution<> distribution {min, max};

	return distribution(generator);
}


std::string randomString
(
	std::size_t length,
	std::string characters = "0123456789"
							 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
							 "abcdefghijklmnopqrstuvwxyz"
)
{
	std::string s;
    for (std::size_t i {0}; i < length; ++i)
    {
        s += characters
		[
			randomInt(0, characters.size() - 1)
		];
    }

    return s;
}


void compareTest
(
	bool& pass,
	const bool test,
	const bool output,
	const std::string& testString
)
{
	auto totalWidth {30};
	auto outputWidth {totalWidth - testString.size() - 3};

	if (output)
		std::cout << testString << "...";

	if (test)
	{
		if (output)
			std::cout << std::setw(outputWidth) << "PASS\n";
	}
	else
	{
		if (output)
			std::cout << std::setw(outputWidth) << "FAIL\n";
		pass = false;
	}
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace test
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
