/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Airfoil class functionality.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "Airfoil.h"
#include "General.h"
#include "Geometry.h"
#include "InputRegistry.h"
#include "Variables.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[]) {

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	input::InputRegistry::store					// TODO: should mass test this
	(
		HashMap<String>
		{
			// machine
			{"Density",						"1.2"},
			{"Rps",							"116.666"},
			{"TotalPressureDifference",		"400"},
			{"VolumeFlowRate",				"0.222"},
			// blade/blade row
			{"HubRadius",					"0.0375"},
			{"IncidenceAngle",				"0.0"},		// default
			{"NumberOfBlades",				"6"},
			{"ShroudRadius",				"0.075"},
			{"Solidity",					"1.0"},		// default
			{"VortexDistributionExponent",	"-1.0"},	// default
			// airfoil
			{"Distribution",				"Naca4DigitDistribution"},
			{"MaxProfileThickness",			"0.1"},
			{"Camber",						"CircularArcCamber"},
			{"CamberPointSpacing",			"Cosine"},	// default
			{"NumberOfCamberPoints",		"150"}		// default
		}
	);

	// 'Airfoil' needs this data,
	// although it would normally be supplied by
	// someone else (owner) eg. 'Blade'.
	// Formally we could compute these and
	// store them to into the InputRegistry as well.
	input::Radius radius {0.05625};	// mean radius
	input::InletVelocity c_1
	{
		input::read<input::VolumeFlowRate>(),
		input::read<input::HubRadius>(),
		input::read<input::ShroudRadius>()
	};
	input::RootOutletVelocity c_2_h
	{
		c_1,
		input::read<input::TotalPressureDifference>(),
		input::read<input::Rps>(),
		input::read<input::HubRadius>(),
		input::read<input::Density>()
	};

	// an owner registry to store
	// the values needed by 'Airfoil'
	// Formally these could be read from
	// the InputRegistry if they were stored.
	input::Registry reg {};
	input::storeAll(reg, c_1, c_2_h);

	// make the 'Airfoil'
	design::Airfoil airfoil {radius, reg};

	// show all the geometry 
	auto points
	{
		airfoil.profile.getPoints()
	};
	auto contour
	{
		airfoil.profile.getContour()
	};
	auto trailingEdge
	{
		airfoil.profile.getTrailingEdge()
	};

	test::updateAndWait(1, output);

	// (150 * 2 - 1) points, 1 spline & 2 points, 1 line & 2 points
	test::compareTest
	(
		pass,
		(
			test::getNumberOfEntities() == 305
		),
		output,
		"Checking entitites after construction"
	);
	test::updateAndWait(1, output);

	// shouldn't be wrapped
	test::compareTest
	(
		pass,
		!airfoil.profile.wrapped(),
		output,
		"Checking if not wrapped"
	);

	// wrap
	airfoil.profile.wrap();

	// should be wrapped
	test::compareTest
	(
		pass,
		airfoil.profile.wrapped(),
		output,
		"Checking if wrapped"
	);

	// show all the geometry 
	auto wrappedPoints
	{
		airfoil.profile.getPoints()
	};
	auto wrappedContour
	{
		airfoil.profile.getContour()
	};
	auto wrappedTrailingEdge
	{
		airfoil.profile.getTrailingEdge()
	};

	test::updateAndWait(1, output);

	// 2 x what it was before
	test::compareTest
	(
		pass,
		(
			test::getNumberOfEntities() == 610
		),
		output,
		"Checking entitites after wrapping"
	);
	test::updateAndWait(1, output);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
