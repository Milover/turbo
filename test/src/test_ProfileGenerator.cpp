/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing ProfileGenerator class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <iostream>
#include <utility>
#include <vector>

#include "gmsh.h"

#include "ProfileGenerator.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", output);
	bool pass {true};

	// test construction

	Stringmap<> input
	{
		{"distribution", "naca4Digit"},
		{"maxThickness", "0.2"},
		{"camber", "naca2Digit"}
	};

	// test
	for (int camberAngle {5}; camberAngle < 70; camberAngle += 5)
	{
		std::cout << "\ncamber angle: " << camberAngle << '\n';

		// default constructor
		geometry::ProfileGenerator temp {input};
		geometry::ProfileGenerator generator {std::move(temp)};

		// test construction related stuff
		test::compareTest
		(
			pass,
			generator.empty(),
			output,
			"Checking empty()"
		);
		test::compareTest
		(
			pass,
			(generator.size() == 0),
			output,
			"Checking size()"
		);

		// test generation related stuff
		generator.generate(camberAngle);
		test::compareTest
		(
			pass,
			!generator.empty(),
			output,
			"Checking empty()"
		);
		test::compareTest
		(
			pass,
			(generator.size() == 199),
			output,
			"Checking size()"
		);
		test::compareTest
		(
			pass,
			generator.hasValue("maxCamber"),
			output,
			"Checking hasValue()"
		);
		test::compareTest
		(
			pass,
			generator.hasValue("maxCamberPosition"),
			output,
			"Checking hasValue()"
		);

		// test range for loop
		std::vector<int> points;
		for (auto point : generator)
			points.push_back
			(
				gmsh::model::geo::addPoint
				(
					point[0],
					point[1],
					point[2]
				)
			);
		if (output)
		{
			std::cout << "max camber: " << generator.get("maxCamber") << '\n';
			std::cout << "max camber position: " << generator.get("maxCamberPosition") << '\n';
		}
		test::updateAndWait(1, output);


		test::compareTest
		(
			pass,
			(points.size() == 199),
			output,
			"Checking number of points"
		);

		// checking inclinations
		test::compareTest
		(
			pass,
			isGreaterOrEqual
			(
				generator.get("leadingInclination"), 0.0
			),
			output,
			"Checking LE inclination"
		);
		test::compareTest
		(
			pass,
			isLessOrEqual
			(
				generator.get("trailingInclination"), 0.0
			),
			output,
			"Checking TE inclination"
		);

		// remove points
		Vectorpair<int> dimTags;
		for (auto i : points)
			dimTags.push_back
			(
				std::make_pair(0, i)
			);

		gmsh::model::geo::remove(dimTags);
	}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);

	test::finalize(output);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
