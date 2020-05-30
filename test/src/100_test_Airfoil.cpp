/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Airfoil class functionality.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

	NOTE: reference:

		  Buchwald, P. & Vogt, D. M. & Grillat, J. & Laufer, W. &
		  Schmitz, M. B. & Lucius, A. & Schneider, M. (2017).
		  Aeroacoustic Analysis of Low-Speed Axial Fans with Different
		  Rotational Speeds in the Design Point.
		  Journal of Engineering for Gas Turbines and Power,
		  doi: 10.1115/1.4038122

		  NOTE: required total pressure changed to static pressure

\*---------------------------------------------------------------------------*/

#include <filesystem>
#include <fstream>

#include "Airfoil.h"
#include "General.h"
#include "GmshControl.h"
#include "InputRegistry.h"
#include "Registry.h"
#include "Simulator.h"
#include "Variables.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	//control.set("General.Verbosity", 10);

	input::InputRegistry::store					// TODO: should mass test this
	(
		HashMap<String>
		{
			// machine
			{"Density",						"1.2"},
			{"DynamicViscosity",			"1.8206e-5"},
			{"Rps",							"116.666"},
			{"StaticPressureDifference",	"400"},
			{"VolumeFlowRate",				"0.222"},
			{"TurbulenceReferenceLengthScaleRatio",	"0.1"},		// default
			{"TurbulenceIntensity",			"0.05"},			// default
			// blade/blade row
			{"HubRadius",					"0.0375"},
			{"IncidenceAngle",				"0"},				// default
			{"NumberOfBlades",				"6"},
			{"NumberOfStations",			"1"},				// default
			{"ShroudRadius",				"0.075"},
			{"TipClearance",				"0"},				// default
			{"Solidity",					"1.0"},				// default
			// airfoil
			{"Distribution",	"Naca4DigitDistribution"},		// default
			{"DeviationAngle",				"0"},				// default
			{"MaxProfileThickness",			"0.1"},
			{"Camber",				"CircularArcCamber"},		// default
			{"CamberPointSpacing",			"Cosine"},			// default
			{"NumberOfCamberPoints",		"150"},				// default
			// mesh
			{"ProfileMeshGenerator","ProfileTetMeshGenerator"},	// default
			{"RelMeshSize",					"0.01"},			// default
			{"SectionExtensionFactor",		"1.0"},				// default
			//{"BLNumberOfLayers",			"5"},				// disabled
			{"BLGrowthRate",				"1.2"},				// default
			{"BLTransitionRatio",			"0.75"},			// default
			{"ProfileBumpFactor",			"0.25"},			// default
			{"YPlus",						"1"},
			// precomputed values, because 'Blade' is not present
			{"KinematicViscosity",			"1.5172e-5"},
			{"InletVelocity",				"(16.7502 0 0)"},
			{"RootOutletVelocity",			"(16.7502 -24.2523 0)"},
			{"VortexDistributionExponent",	"-1.0"},			// default
			{"TurbulenceKineticEnergy",		"1.0521"}
		}
	);

	// A dummy Registry, so Airfoil
	// can read the values from the InputRegistry
	input::Registry reg {};

	// make Airfoil
	design::Airfoil airfoil
	{
		input::Radius {0.05625},
		reg,
		std::move(model)
	};
	airfoil.build();

	// show all geometry 
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

	updateAndWait(1);

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
	updateAndWait(1);

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
	updateAndWait(1);

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
	updateAndWait(1);

	// reset and test simulation
	airfoil.build();

debug::echo("inlet metal angle:   \t", angleBetween(airfoil.profile.leDirection(), -Vector::yAxis()));
debug::echo("inlet relative angle:\t", angleBetween(airfoil.get<input::InletRelativeVelocity>().value(), Vector::yAxis()));

	// data dump
	std::ofstream ofs {airfoil.cwd() / "data"};
	airfoil.printAll(ofs, 40);
	ofs.flush();

	// make a new mesh
	auto caseDir {airfoil.simulate()};

	// check if the airfoil cwd was properly built
	test::compareTest
	(
		pass,
		(
			std::filesystem::exists(airfoil.cwd())
		),
		output,
		"Checking airfoil directory"
	);

	// check if the case dir was properly built
	test::compareTest
	(
		pass,
		(
			std::filesystem::exists(caseDir)
		),
		output,
		"Checking case directory"
	);

	control.update();
	control.run();

	// cleanup
	auto r_2 {std::filesystem::remove_all(airfoil.cwd())};
	auto r_1 {std::filesystem::remove_all("turbo_case_template")};

	// we should have cleaned something up
	pass = pass
		&& r_1 > 0
		&& r_2 > 0;

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
