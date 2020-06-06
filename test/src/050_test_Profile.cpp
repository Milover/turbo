/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Profile class.

	TODO: some numeric (comparison) tests would be nice,
		  mostly visuals checks for now

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "General.h"
#include "GmshControl.h"
#include "InputRegistry.h"
#include "Model.h"
#include "Profile.h"
#include "ProfileGenerator.h"
#include "Registry.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	#include "TestInclude.h"
	#include "TestGmshInclude.h"

	input::InputRegistry::store					// TODO: should mass test this
	(
		HashMap<String>
		{
			{"CamberPointSpacing",		"Cosine"},
			{"Thickness",				"Naca4DigitThickness"},
			{"Camber",					"CircularArcCamber"},
			{"NumberOfCamberPoints",	"250"},
			{"MaxProfileThickness",		"0.1"},
			// precomputed values, because 'Airfoil' is not present
			{"CamberAngle",				std::to_string(0.25 * M_PI)},
			{"Chord",					"0.5"},
			{"Radius",					"1.0"},
			{"StaggerAngle",			std::to_string(0.5 * M_PI)}
		}
	);

	// A dummy Registry, so Profile and ProfileGenerator
	// can read the values from the InputRegistry
	input::Registry reg {};

	design::ProfileGenerator generator {reg};
	design::Profile profile;

	// build
	profile.build(generator, reg);

	// should be cenetered on z-axis
	// and offset by the radius
	// (+/- fp errors because of summation)
	Vector pc {profile.centroid()};
	test::compareTest
	(
		pass,
		(
			(std::abs(pc.x() - 0.0) < test::eps)
		 && (std::abs(pc.y() - 0.0) < test::eps)
		 && (std::abs(pc.z() - reg.cref<input::Radius>().value()) < test::eps)
		),
		output,
		"Checking if centered"
	);

	// show all geometry 
	auto points {profile.getPoints()};
	auto contour {profile.getContour()};
	auto trailingEdge {profile.getTrailingEdge()};

	updateAndWait(1);
	// (250 * 2 - 1) points, 1 spline & 2 points, 1 line & 2 points
	test::compareTest
	(
		pass,
		(
			test::getNumberOfEntities() == 505
		),
		output,
		"Checking entitites after build"
	);
	updateAndWait(1);

	// shouldn't be wrapped
	test::compareTest
	(
		pass,
		!profile.wrapped(),
		output,
		"Checking if not wrapped"
	);

	// wrap
	profile.wrap();

	// show all the geometry 
	auto wrappedPoints {profile.getPoints()};
	auto wrappedContour {profile.getContour()};
	auto wrappedTrailingEdge {profile.getTrailingEdge()};

	updateAndWait(1);

	// 2 x what it was before
	test::compareTest
	(
		pass,
		(
			test::getNumberOfEntities() == 1010
		),
		output,
		"Checking entitites after wrap"
	);
	updateAndWait(1);

	// should be wrapped
	test::compareTest
	(
		pass,
		profile.wrapped(),
		output,
		"Checking if wrapped"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);

	control.update();
	control.run();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
