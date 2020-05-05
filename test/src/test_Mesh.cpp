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
#include "GmshControl.h"
#include "Geometry.h"
#include "InputRegistry.h"
#include "Variables.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	// profile stuff
	input::CamberAngle camber	{0.25 * M_PI};	// TODO: should mass test this
	input::Chord chord			{0.5};			// so we can see the scaling
	input::Pitch pitch			{0.5};			// generic pitch
	input::Radius radius		{1.0};			// so we can see the translation and wrap
	input::StaggerAngle stagger	{0.5 * M_PI};	// so we can see the rotation
	// mesh stuff

	input::InputRegistry::store					// TODO: should mass test this
	(
		HashMap<String>
		{
			{"CamberPointSpacing",		"Linear"},
			{"Distribution",			"ConstantDistribution"},
			{"Camber",					"CircularArcCamber"},
			//{"NumberOfCamberPoints",	"250"},
			{"MaxProfileThickness",		"0.1"}
			{"Solidity",				"1.0"},		// default
		}
	);

	design::ProfileGenerator generator {camber};
	design::Profile profile;

	// build
	profile.build
	(
		generator,
		chord,
		radius,
		stagger
	);

	mesh::Mesh mesh
	{

	};


	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
