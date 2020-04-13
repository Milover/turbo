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

#include <cassert>
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

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace test
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// a handy dandy precison for when isEqual() fails
inline static constexpr Float eps {1e-15};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void initialize
(
	String s,
	const bool gui = true
)
{
	if (gui)
	{
		gmsh::initialize(0, 0, false);
		gmsh::fltk::initialize();
		gmsh::option::setNumber("General.Terminal", 1);
		gmsh::option::setNumber("General.Verbosity", 1);
		gmsh::option::setNumber("Geometry.Surfaces", 1);
		gmsh::option::setNumber("Geometry.SurfaceNumbers", 1);
		gmsh::option::setNumber("Geometry.SurfaceType", 2);
		gmsh::option::setNumber("Geometry.NumSubEdges", 200);
	}
	else
	{
		gmsh::initialize(0, 0, false);
	}
	gmsh::option::setNumber("General.NumThreads", 0);
	gmsh::option::setNumber("Geometry.AutoCoherence", 0);
	gmsh::option::setNumber("Geometry.Tolerance", 1e-17);
	gmsh::model::add(s);
}


void initializeNoModel(const bool gui = true)
{
	if (gui)
	{
		gmsh::initialize();
		gmsh::fltk::initialize();
		gmsh::option::setNumber("General.Terminal", 1);
		gmsh::option::setNumber("General.Verbosity", 100);
		gmsh::option::setNumber("Geometry.Surfaces", 1);
		gmsh::option::setNumber("Geometry.SurfaceNumbers", 1);
		gmsh::option::setNumber("Geometry.SurfaceType", 2);
		gmsh::option::setNumber("Geometry.NumSubEdges", 200);
	}
	else
	{
		gmsh::initialize(0, 0, false);
	}
	gmsh::option::setNumber("General.NumThreads", 0);
	gmsh::option::setNumber("Geometry.AutoCoherence", 0);
	gmsh::option::setNumber("Geometry.Tolerance", 1e-17);
}


void update(const bool gui)
{
	gmsh::model::occ::synchronize();

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
	const Integer d [[maybe_unused]],
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
	turbo::Vectorpair<Integer> v;
	gmsh::model::getEntities(v);

	for (const auto& [dim, tag] : v)
	{
		echo("entity dimTag: ", dim, ' ', tag);
	}
}


Integer getNumberOfEntities()
{
	turbo::Vectorpair<Integer> v;
	gmsh::model::getEntities(v);

	return v.size();
}

bool parseCommandLineArgs
(
	Integer argc,
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


Integer randomInt
(
	Integer min,
	Integer max
)
{
	assert(min < max);

    std::random_device randomDevice;
    std::mt19937 generator {randomDevice()};
    std::uniform_int_distribution<> distribution {min, max};

	return distribution(generator);
}


bool randomBool()
{
	return static_cast<bool>(randomInt(0, 1));
}


String randomString
(
	std::size_t length,
	String characters = "0123456789"
					  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					  "abcdefghijklmnopqrstuvwxyz"
)
{
	String s;
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
	const String& testString
)
{
	auto totalWidth {50};
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
