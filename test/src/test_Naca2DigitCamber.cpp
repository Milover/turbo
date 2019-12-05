/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Naca2DigitCamber class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <iostream>
#include <utility>
#include <vector>

#include "Naca2DigitCamber.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// test construction

	Stringmap<> input_1 {};
	Stringmap<> input_2
	{
		{"camberPoints", "100"},
		{"spacing", "linear"},
		{"maxCamberPosition", "0.5"}
	};

	// test
	for (int camberAngle {5}; camberAngle < 70; camberAngle += 5)
	{
		std::cout << "\ncamber angle: " << camberAngle << '\n';

		// default constructor
		std::vector<geometry::Naca2DigitCamber> generators_;
		generators_.push_back
		(
			geometry::Naca2DigitCamber {input_1}
		);
		generators_.push_back
		(
			geometry::Naca2DigitCamber {input_2}
		);

		// move constructor
		geometry::Naca2DigitCamber temp {input_2};
		generators_.push_back
		(
			geometry::Naca2DigitCamber {std::move(temp)}
		);

		for (auto& g : generators_)
		{
			// test construction related stuff
			test::compareTest
			(
				pass,
				g.empty(),
				output,
				"Checking empty()"
			);
			test::compareTest
			(
				pass,
				(g.size() == 0),
				output,
				"Checking size()"
			);
			test::compareTest
			(
				pass,
				g.hasKey("maxCamberPosition"),
				output,
				"Checking hasKey()"
			);
			test::compareTest
			(
				pass,
				g.hasValue("maxCamberPosition"),
				output,
				"Checking hasValue()"
			);
			test::compareTest
			(
				pass,
				isEqual
				(
					g.get("maxCamberPosition"), 0.5
				),
				output,
				"Checking get()"
			);

			// test generation related stuff
			g.generate(camberAngle);
			test::compareTest
			(
				pass,
				!g.empty(),
				output,
				"Checking empty()"
			);
			test::compareTest
			(
				pass,
				(g.size() == 100),
				output,
				"Checking size()"
			);
			test::compareTest
			(
				pass,
				g.hasKey("maxCamber"),
				output,
				"Checking hasKey()"
			);
			test::compareTest
			(
				pass,
				g.hasValue("maxCamber"),
				output,
				"Checking hasValue()"
			);

			if (output)
			{
				std::cout << "max camber: " << g.get("maxCamber") << '\n';
				std::cout << "max camber position: " << g.get("maxCamberPosition") << '\n';
			}

			// test range for loop
			int count {0};
			for ([[maybe_unused]] auto i : g)
				count++;

			test::compareTest
			(
				pass,
				(count == 100),
				output,
				"Checking number of points"
			);

			// checking inclinations
			test::compareTest
			(
				pass,
				isGreaterOrEqual
				(
					g.getInclinationAt(0.0), 0.0
				),
				output,
				"Checking LE inclination"
			);
			test::compareTest
			(
				pass,
				isLessOrEqual
				(
					g.getInclinationAt(1.0), 0.0
				),
				output,
				"Checking TE inclination"
			);
		}
	}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
