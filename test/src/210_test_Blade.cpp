/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Airfoil class functionality.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

	NOTE: Koncar MES VAAZ-C 800 redesign


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

	input::InputRegistry::store
	(
		HashMap<String>
		{
			// general
			{"Density",								"1.2"},
			{"DynamicViscosity",					"1.8206e-5"},
			{"Rps",									"11.83334"},
			{"StaticPressureDifference",			"155"},
			{"VolumeFlowRate",						"4.16667"},
			{"TurbulenceReferenceLengthScaleRatio",	"0.1"},		// default
			{"TurbulenceIntensity",					"0.05"},	// default
			// blade
			{"HubRadius",							"0.075"},
			{"IncidenceAngle",						"0"},		// default
			{"MaxAbsBladeThicknessDistribution","(0.0095 0.008)"},	// optional
			{"MaxPassageWidthDistribution",			"(0.1)"},	// optional
			{"NumberOfBlades",						"7"},
			{"NumberOfStations",					"3"},
			{"ShroudRadius",						"0.3975"},
			{"TipClearance",						"0"},		// default
			{"SolidityDistribution",			"(1.2 0.5)"},	// nondefault
			{"SkewDistribution",					"BezierTangential"},
			{"HubSkewAngle",						"0.0"},		// default
			{"ShroudSkewAngle",						"0.5236"},	// ~30°
			{"BezierSkewRelativeRadius",			"0.5"},		// default
			//{"VortexDistributionExponent",			"1.3"},		// optional
			{"RootOutletVelocity",			"(8.70378 -1.68 0)"},	// optional
			// airfoil
			{"Thickness",				"Naca4DigitThickness"},	// default
			{"DeviationAngle",						"0"},		// default
			{"MaxProfileThickness",					"0.1"},
			{"MonitoringPlaneOffset",				"0.05"},	// default
			{"Camber",					"CircularArcCamber"},	// default
			{"CamberPointSpacing",					"Cosine"},	// default
			{"NumberOfCamberPoints",				"150"},		// nondefault
			// mesh
			{"ProfileMeshGenerator","ProfileTetMeshGenerator"},	// default
			{"RelMeshSize",							"0.01"},	// default
			{"SectionExtensionFactor",				"1.0"},		// default
			//{"BLNumberOfLayers",					"5"},		// disabled
			{"BLGrowthRate",						"1.2"},		// default
			{"BLTransitionRatio",					"0.75"},	// default
			{"ProfileBumpFactor",					"0.25"},	// default
			{"YPlus",								"1"}		// nondefault
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
		airfoil->simulate();
		airfoil->dumpData();
	}
	blade.dumpData();

	// build the blade
	blade.build();
	blade.write();

	updateAndWait(1);

	control.update();
	control.run();

	// cleanup
	pass = pass && std::filesystem::remove_all(blade.cwd()) > 0;
	pass = pass && std::filesystem::remove_all("turbo_case_template") > 0;

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
