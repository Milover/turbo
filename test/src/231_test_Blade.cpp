/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Integrated design test.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

	NOTE: Generic axial fan design test case.


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
			{"Rps",									"16.0"},	// 960 min-1
			{"TargetStaticPressureDifference",		"100"},
			{"TurbulenceReferenceLengthScaleRatio",	"0.1"},		// default
			{"TurbulenceIntensity",					"0.05"},	// default
			{"VolumeFlowRate",						"7.37"},	// 26458 m3h-1
			// blade
			{"HubRadius",							"0.1"},
			//{"IncidenceAngle",					"0"},		// disabled
			{"MaxAbsBladeThicknessDistribution",	"(0.01 0.008)"},// optional
			{"MaxPassageWidthDistribution",			"(0.15)"},		// optional
			{"NumberOfBlades",						"8"},
			{"NumberOfStations",					"5"},
			{"ShroudRadius",						"0.5"},
			{"TipClearance",						"0"},		// default
			{"SolidityDistribution",			"(1.2 0.8)"},	// nondefault
			//{"CamberAngleScalingFactorDistribution","(1.0 3.0)"},		// disabled
			{"SkewDistribution",					"NoSkew"},	// deafult
			{"HubSkewAngle",						"0.0"},		// default
			{"ShroudSkewAngle",						"0.0"},		// default
			{"BezierSkewRelativeRadius",			"0.5"},		// default
			{"VortexDistributionExponent",			"-1"},		// optional
			//{"RootOutletVelocity",			"(9.77477 -2.56 0)"},	// optional
			// airfoil
			{"Thickness",				"Naca4DigitThickness"},	// default
			//{"DeviationAngle",						"0"},	// disabled
			{"MaxProfileThickness",					"0.1"},
			{"MonitoringPlaneOffset",				"0.05"},	// default
			{"Camber",					"CircularArcCamber"},	// default
			{"CamberPointSpacing",					"Cosine"},	// default
			{"NumberOfCamberPoints",				"250"},		// nondefault
			{"DesignPressureRelTolerance",			"0.025"},	// default
			{"StagnationPointDesignPrecision",		"2.5e-4"},	// nondefault
			{"StaggerAngleRelDesignPrecision",		"0.25"},	// default
			{"CamberAngleRelDesignPrecision",		"0.25"},	// nondefault
			{"CamberAngleDesignLimit",				"3.0"},		// default
			{"MaxDesignIter",						"100"},		// default
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

	// dump the initial data
	blade.dumpData();

	design::Airfoil::DesignData dd;
	const auto& airfoils {blade.airfoilsCRef()};
	for (auto& a : airfoils)
		dd = a->design(dd);

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
