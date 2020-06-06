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

#include "Blade.h"
#include "General.h"
#include "GmshControl.h"
#include "InputRegistry.h"
#include "Line.h"
#include "Registry.h"
#include "Simulator.h"
#include "Spline.h"
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
			{"AerodynamicEfficiency",		"0.6"},				// default
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
			{"NumberOfStations",			"3"},
			{"ShroudRadius",				"0.075"},
			{"TipClearance",				"0"},				// default
			{"Solidity",					"1.0"},				// default
			// airfoil
			{"Thickness",			"Naca4DigitThickness"},		// default
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
			{"YPlus",						"150"}				// default
		}
	);

	// A dummy Registry, so Airfoil
	// can read the values from the InputRegistry
	input::Registry reg {};

	// make Blade
	design::Blade blade
	{
		reg,
		std::move(model)
	};

	for (const auto& airfoil : blade.airfoilsCRef())
	{
		airfoil->build();
		airfoil->dumpData();
	}
	blade.dumpData();

	updateAndWait(1);

	// build the blade
	blade.build();

	updateAndWait(1);

	control.update();
	control.run();

	// cleanup
	pass = pass && std::filesystem::remove_all(blade.cwd()) > 0;

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
