/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing NacaProfileGenerator class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <cstdlib>
#include <map>
#include <random>
#include <stdexcept>
#include <string>

#include "NacaProfileGenerator.h"
#include "Utility.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// some functions to help automate the testing

// return an well defined 4-digit (modified) series string
std::string goodSeries()
{
	std::string s {test::randomString(1, "0123456789")};	// m

	if (s == "0")
		s += "0";									// p (symmetric)
	else
		s += test::randomString(1, "123456789");	// p (asymmetric)
	
	s += test::randomString(2, "0123456789");		// xx

	// 4-digit modified
	if (test::randomInt(0, 1))
	{
		s += "-";
		s += test::randomString(1, "0123456789");	// I
		s += test::randomString(1, "23456");		// M
	}

	return s;
}


// return an ill-defined 4-digit (modified) series string
std::string badSeries()
{
	switch (test::randomInt(1, 1))
	{
		// random position of '-'
		case 1:
		{
			std::string s
			{
				test::randomString(5, "0123456789")		// mpxxI
			};
			s += test::randomString(1, "23456");		// M

			int at {0};
			if (s.size() == 0)
				at = 0;
			else
				at = test::randomInt(0, s.size() - 1);

			s.insert(at, "-");
			return s;
			break;
		}
		// garbage with correct number of digits
		case 2:
		{
			// 4-digit
			if (test::randomInt(0, 1))
			{
				return test::randomString(4);
			}
			// 4-digit modified
			else
			{
				return test::randomString(7);
			}
			break;
		}
		// garbage of random size (and position of '-')
		default:
		{
			std::string s
			{
				test::randomString(test::randomInt(0, 20))
			};
			// 4-digit modified
			if (test::randomInt(0, 1))
			{
				int at;
				if (s.size() == 0)
					at = 0;
				else
					at = test::randomInt(0, s.size() - 1);

				s.insert(at, "-");
			}

			return s;
			break;
		}
	}
}

Stringmap constructInput()
{
	switch (test::randomInt(1, 5))
	{
		// all good
		case 1:
		{
			return Stringmap
			{
				{"series", goodSeries()},
				{"numberOfPoints", "10"},		// value not important here
				{"spacingType", "linear"}		// value not important here

			};
			break;
		}
		// bad series
		case 2:
		{
			return Stringmap
			{
				{"series", badSeries()},
				{"numberOfPoints", "10"},		// value not important here
				{"spacingType", "linear"}		// value not important here
			};
			break;
		}
		// bad number of points
		case 3:
		{
			return Stringmap
			{
				{"series", goodSeries()},
				{"numberOfPoints", std::to_string(-1 * test::randomInt(20, 40))},
				{"spacingType", "linear"}		// value not important here

			};
			break;
		}
		// bad spacing type
		case 4:
		{
			return Stringmap
			{
				{"series", goodSeries()},
				{"numberOfPoints", "10"},		// value not important here
				{"spacingType", test::randomString(test::randomInt(0, 20))}

			};
			break;
		}
		// garbage
		default:
		{
			return Stringmap
			{
				{"series", badSeries()},
				{"numberOfPoints", std::to_string(-1 * test::randomInt(20, 40))},
				{"spacingType", test::randomString(test::randomInt(0, 20))}
			};
			break;
		}
	}
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	
	bool pass {true};

	// NOTE:	CAMBERED AIRFOILS NOT IMPLEMENTED!
	
	// input testing

	// the loop should finish by itself i.e. all exceptions should be caught
	for (std::size_t i {0}; i < 250; i++)
	{
		Stringmap input {constructInput()};

		if (output)
			test::echo
			(
				"Test: ", i, '\n',
				"series",			"\t\t",	input["series"],			'\n',
				"numberOfPoints",	'\t',	input["numberOfPoints"],	'\n',
				"spacingType",		'\t',	input["spacingType"],		'\n'
			);

		try
		{
			geometry::NacaProfileGenerator g {input};
		}
		catch(std::invalid_argument& e)
		{}
		catch(std::runtime_error& e)
		{}
	}

	// profile generation testing


	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

