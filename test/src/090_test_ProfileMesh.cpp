/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Mesh class.

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
#include "Utility.h"
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
			{"DynamicViscosity",		"1.8206e-5"},
			{"Density",					"1.2"},
			// profile
			{"CamberPointSpacing",		"Cosine"},	// default
			{"Distribution",			"Naca4DigitDistribution"},	// default
			{"Camber",					"CircularArcCamber"},		// default
			{"NumberOfCamberPoints",	"150"},		// default
			{"MaxProfileThickness",		"0.1"},
			{"Solidity",				"1.0"},		// default
			// mesh
			{"ProfileMeshGenerator",	"ProfileTetMeshGenerator"},	// default
			//{"MeshSize",				"20000"},	// disabled
			{"MeshCellSize",			"0.005"},
			//{"BLNumberOfLayers",		"5"},		// disabled
			{"BLGrowthRate",			"1.2"},		// default
			{"BLTransitionRatio",		"0.4"},	// default
			{"ProfileBumpFactor",		"0.25"},	// default
			// precomputed values because 'Airfoil' is not present
			{"InletVelocity",			"16.7502 0.0 0.0"},
			{"BladeVelocity",			"0.0 315.0 0.0"},
			{"CamberAngle",				std::to_string(0.15 * M_PI)},
			{"Chord",					"0.5"},
			{"Pitch",					"0.4"},
			{"Radius",					"1.0"},
			{"StaggerAngle",			std::to_string(0.417 * M_PI)}
		}
	);

	// A dummy Registry, so things
	// can read the values from the InputRegistry
	input::Registry reg {};

	// build profile
	design::ProfileGenerator pg {reg};
	design::Profile profile {};
	profile.build(pg, reg);

	updateAndWait(1);

	// build mesh
	mesh::ProfileMesh mesh {reg, std::move(model)};
	mesh.build(profile);

	updateAndWait(1);

	mesh.write();

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();

	if (std::filesystem::exists(mesh.filename))
		std::filesystem::remove(mesh.filename);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
