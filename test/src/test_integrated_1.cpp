/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Integrated test 1.
	Testing Machine, BladeRow, Blade and Airfoil classes.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "Machine.h"
#include "BladeRow.h"
#include "Blade.h"
#include "Airfoil.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initializeNoModel(output);
	bool pass {true};

	// test construction

	Stringmap<> input
	{
		// machine
		{"deltaP",				"400"},		// [Pa]
		{"density",				"1.2"},		// [kg m-3]
		{"rpm",					"7000"},	// [min-1]
		{"volumeFlowRate",		"800"},		// [m3 h-1]
		// blade row
		{"hubShroudRatio",		"0.5"},		// [-]		- default
		{"numberOfBlades",		"5"},		// [-]		
		{"tipGap",				"0.001"},	// [m]		- default
		{"shroudRadius",		"0.075"},	// [m]		
		// blade
		{"hubOffset",			"0.0"},		// [m]		- default
		{"numberOfStations",	"50"},		//
		{"tipOffset",			"0.0"},		// [m]		- default
		{"vortexLawExponent",	"0.6"},		// [-]		- default
		// airfoil
		{"incidence",			"0"},		// [deg]	- default
		{"solidity",			"1"},		// [-]		- default
		// deviation
		{"deviation",			"carter"},
		// distribution generator
		{"distribution",		"naca4Digit"},
		{"maxThickness",		"0.1"},		// [-] - % of chord
		// camber generator
		{"camberPoints",		"100"},		//			- default
		{"spacing",				"cosine"},	//			- default
		{"camber",				"naca2Digit"},
		{"maxCamberPosition",	"0.5"}		// [-] - % of chord - default
	};

	geometry::Machine machine {input};

	// test
	machine.build();
	test::updateAndWait(1, output);

	//gmsh::write("/home/philipp/workspace/test.step");

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
