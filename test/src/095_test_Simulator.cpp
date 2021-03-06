/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Simulator class.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "General.h"
#include "GmshControl.h"
#include "InputRegistry.h"
#include "ProfileMesh.h"
#include "Profile.h"
#include "ProfileGenerator.h"
#include "Registry.h"
#include "Simulator.h"
#include "Utility.h"

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
			{"DynamicViscosity",					"1.8206e-5"},
			{"Density",								"1.2"},
			{"TurbulenceReferenceLengthScaleRatio",	"0.1"},		// default
			{"TurbulenceIntensity",					"0.05"},	// default
			{"StaticPressureDifference",			"400"},		// default
			// profile
			{"CamberPointSpacing",					"Cosine"},	// default
			{"Thickness",				"Naca4DigitThickness"},	// default
			{"Camber",					"CircularArcCamber"},	// default
			{"NumberOfCamberPoints",				"150"},		// default
			{"MaxProfileThickness",					"0.1"},
			{"SolidityDistribution",				"(1)"},		// default
			// mesh
			{"ProfileMeshGenerator","ProfileTetMeshGenerator"},	// default
			{"RelMeshSize",							"0.01"},	// default
			{"SectionExtensionFactor",				"1.0"},		// default
			//{"BLNumberOfLayers",					"5"},		// disabled
			{"BLGrowthRate",						"1.2"},		// default
			{"BLTransitionRatio",					"0.75"},	// default
			{"ProfileBumpFactor",					"0.25"},	// default
			// precomputed values because 'Blade'/'Airfoil' aren't present
			{"KinematicViscosity",					"1.5172e-5"},
			{"KinematicPressureDifference",			"333.3333"},
			{"InletVelocity",						"(16.7502 0 0)"},
			{"BladeVelocity",						"(0 -24.2523 0)"},
			{"InletRelativeVelocity",				"(16.7502 24.2523 0)"},
			{"CamberAngle",							std::to_string(0.15 * M_PI)},
			{"Chord",								"0.5"},
			{"Pitch",								"0.5"},
			{"Radius",								"1.0"},
			{"StaggerAngle",						std::to_string(0.4 * M_PI)},
			{"TurbulenceReferenceLengthScale",		"0.05"},
			{"TurbulenceKineticEnergy",				"100"},
			{"TurbulenceDissipationRate",			"200"},
			{"TurbulenceSpecificDissipationRate",	"300"},
			{"TurbulenceViscosity",					"400"},
			{"InletRefPoint",						"(-0.563228 -0.242321 1)"},
			{"TranslationPerBot",				    "(0 0.5 0)"},
			{"TranslationPerTop",				    "(0 -0.5 0)"},
			{"LEMonitoringPlane",				    "(0  1 0)"},
			{"TEMonitoringPlane",				    "(0 -1 0)"}
		}
	);
	// load stuff into the registry
	input::Registry reg {};

	// build profile
	design::ProfileGenerator pg {reg};
	design::Profile profile {};
	profile.build(pg, reg);

	updateAndWait(1);

	// create the simulator so we have a case dir
	simulation::Simulator sim {reg};

	// build mesh
	mesh::ProfileMesh mesh {reg, std::move(model), sim.caseDirectory};
	mesh.build(profile);

	updateAndWait(1);

	mesh.write();

	// simulate
	sim.simulate();

	control.update();
	control.run();

	// cleanup
	auto r_1 {std::filesystem::remove_all(sim.caseDirectory)};
	auto r_2 {std::filesystem::remove_all("turbo_case_template")};

	// we should have cleaned something up
	pass = pass && r_1 > 0 && r_2 > 0;

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
