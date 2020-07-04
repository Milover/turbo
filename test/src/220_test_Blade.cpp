/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Blade class functionality.

	Running simple Airfoil design loops.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

	NOTE: Koncar MES VAAZ-C 800 redesign


\*---------------------------------------------------------------------------*/

#include <filesystem>

#include "Airfoil.h"
#include "Blade.h"
#include "General.h"
#include "GmshControl.h"
#include "InputRegistry.h"
#include "Line.h"
#include "Registry.h"
#include "Simulator.h"
#include "Spline.h"
#include "Timer.h"
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
			{"BladeEfficiency",						"0.85"},
			{"Rps",									"13.66667"},				// 820min-1, was 710min-1
			{"TargetStaticPressureDifference",		"155"},
			{"TurbulenceReferenceLengthScaleRatio",	"0.1"},		// default
			{"TurbulenceIntensity",					"0.05"},	// default
			{"VolumeFlowRate",						"4.16667"},
			// blade
			{"HubRadius",							"0.085"},
			//{"IncidenceAngle",						"0"},	// disabled
			{"MaxAbsBladeThicknessDistribution","(0.0095 0.008)"},	// optional
			{"MaxPassageWidthDistribution",			"(0.1)"},		// optional
			{"NumberOfBlades",						"7"},
			{"NumberOfStations",					"9"},
			{"ShroudRadius",						"0.3975"},
			{"TipClearance",						"0"},		// default
			{"SolidityDistribution",			"(1.2 0.6)"},	// nondefault
			{"CamberAngleScalingFactorDistribution","(1.0 3.0)"},		// temporary
			{"SkewDistribution",					"BezierTangential"},
			{"HubSkewAngle",						"0.0"},		// default
			{"ShroudSkewAngle",						"0.5236"},		// ~30°
			{"BezierSkewRelativeRadius",			"0.5"},		// default
			//{"VortexDistributionExponent",			"1.3"},		// optional
			{"RootOutletVelocity",			"(8.79613 -1.68 0)"},	// optional
			// airfoil
			{"Thickness",				"Naca4DigitThickness"},	// default
			//{"DeviationAngle",						"0"},	// disabled
			{"MaxProfileThickness",					"0.1"},
			{"MonitoringPlaneOffset",				"0.05"},	// default
			{"Camber",					"CircularArcCamber"},	// default
			{"CamberPointSpacing",					"Cosine"},	// default
			{"NumberOfCamberPoints",				"250"},		// nondefault	// was 250
			{"DesignPressureRelTolerance",			"0.025"},	// default
			{"StaggerAngleDesignPrecision",			"0.02"},	// nondefault	// was 5e-3
			//{"MaxDesignIter",						"100"},		// disabled
			// mesh
			{"ProfileMeshGenerator","ProfileTetMeshGenerator"},	// default
			{"RelMeshSize",							"0.01"},	// default
			{"SectionExtensionFactor",				"1.5"},		// default
			//{"BLNumberOfLayers",					"5"},		// disabled
			{"BLGrowthRate",						"1.15"},	// default
			{"BLTransitionRatio",					"0.75"},	// default
			{"ProfileBumpFactor",					"0.05"},	// default
			{"YPlus",								"1"}		// default
		}
	);

	// A dummy Registry, so Airfoil
	// can read the values from the InputRegistry
	input::Registry reg {};

	// make Blade
	design::Blade blade{reg, std::move(model)};

	design::Airfoil::DesignData dd;
	// going from shroud to hub
	const auto& airfoils {blade.airfoilsCRef()};
	for (auto it {airfoils.rbegin()}; it != airfoils.rend(); ++it)
		dd = (*it)->design(dd);

	blade.writeStationData(blade.cwd() / "blade.csv");
	blade.dumpData();

	// build the blade
	blade.activate();
	auto tmp {blade.midPlane()};

	// blade.build() is bugged so we have to build after
	blade.build();
	blade.write();

	updateAndWait(1);

	control.update();
	control.run();

	// cleanup
	//pass = pass && std::filesystem::remove_all(blade.cwd()) > 0;
	//pass = pass && std::filesystem::remove_all("turbo_case_template") > 0;

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
