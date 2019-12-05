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

// computed results for the profiles used in the test

static const Vectorpair<double> NACA_0020_LINEAR
{
	{0.0000000000000000, 0.0000000000000000},
	{0.1000000000000000, 0.0780554237303992},
	{0.2000000000000000, 0.0957809165039375},
	{0.3000000000000000, 0.1000000000000000},
	{0.4000000000000000, 0.0974367346938776},
	{0.5000000000000000, 0.0901224489795918},
	{0.6000000000000000, 0.0786204081632653},
	{0.7000000000000000, 0.0634938775510204},
	{0.7999999999999999, 0.0453061224489796},
	{0.8999999999999999, 0.0246204081632653},
	{0.9999999999999999, 0.0020000000000000},
	{0.0000000000000000, -0.0000000000000000},
	{0.1000000000000000, -0.0780554237303992},
	{0.2000000000000000, -0.0957809165039375},
	{0.3000000000000000, -0.1000000000000000},
	{0.4000000000000000, -0.0974367346938776},
	{0.5000000000000000, -0.0901224489795918},
	{0.6000000000000000, -0.0786204081632653},
	{0.7000000000000000, -0.0634938775510204},
	{0.7999999999999999, -0.0453061224489796},
	{0.8999999999999999, -0.0246204081632653},
	{0.9999999999999999, -0.0020000000000000}
};


static const Vectorpair<double> NACA_0020_COSINE
{
	{0.0000000000000000, 0.0000000000000000},
	{0.0244717418524232, 0.0431555451703475},
	{0.0954915028125262, 0.0767558779324154},
	{0.2061073738537634, 0.0963655011475049},
	{0.3454915028125262, 0.0994589484144480},
	{0.4999999999999999, 0.0901224489795919},
	{0.6545084971874736, 0.0707885738421182},
	{0.7938926261462365, 0.0464942498731162},
	{0.9045084971874737, 0.0236379903610622},
	{0.9755282581475768, 0.0076839466826192},
	{1.0000000000000000, 0.0020000000000000},
	{0.0000000000000000, -0.0000000000000000},
	{0.0244717418524232, -0.0431555451703475},
	{0.0954915028125262, -0.0767558779324154},
	{0.2061073738537634, -0.0963655011475049},
	{0.3454915028125262, -0.0994589484144480},
	{0.4999999999999999, -0.0901224489795919},
	{0.6545084971874736, -0.0707885738421182},
	{0.7938926261462365, -0.0464942498731162},
	{0.9045084971874737, -0.0236379903610622},
	{0.9755282581475768, -0.0076839466826192},
	{1.0000000000000000, -0.0020000000000000}
};


static const Vectorpair<double> NACA_0012_LINEAR
{
	{0.0000000000000000, 0.0000000000000000},
	{0.1000000000000000, 0.0468332542382395},
	{0.2000000000000000, 0.0574685499023625},
	{0.3000000000000000, 0.0600000000000000},
	{0.4000000000000000, 0.0584620408163265},
	{0.5000000000000000, 0.0540734693877551},
	{0.6000000000000000, 0.0471722448979592},
	{0.7000000000000000, 0.0380963265306123},
	{0.7999999999999999, 0.0271836734693878},
	{0.8999999999999999, 0.0147722448979592},
	{0.9999999999999999, 0.0012000000000000},
	{0.0000000000000000, -0.0000000000000000},
	{0.1000000000000000, -0.0468332542382395},
	{0.2000000000000000, -0.0574685499023625},
	{0.3000000000000000, -0.0600000000000000},
	{0.4000000000000000, -0.0584620408163265},
	{0.5000000000000000, -0.0540734693877551},
	{0.6000000000000000, -0.0471722448979592},
	{0.7000000000000000, -0.0380963265306123},
	{0.7999999999999999, -0.0271836734693878},
	{0.8999999999999999, -0.0147722448979592},
	{0.9999999999999999, -0.0012000000000000}
};


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


// build a random well or ill-defined input map
Stringmap constructInput(int type)
{
	switch (type)
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


// compare computed and generated results
bool compareVectorpairs
(
	const Vectorpair<double>& first,
	const Vectorpair<double>& second
)
{
	if (first.size() != second.size())
		return false;

	for (std::size_t i {0}; i < first.size(); i++)
		if
		(
			std::abs(first[i].first - second[i].first) > 1e-16 ||
			std::abs(first[i].second - second[i].second) > 1e-16
		)
			return false;

	return true;
}


// print Vectorpair
void printVectorpair(const Vectorpair<double>& v)
{
	std::cout << std::fixed;
	std::cout.precision(16);
	test::echo("");
	for (auto p : v)
	{
		test::echo(p.first, '\t', p.second);
	}
	test::echo("");
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	bool output {test::parseCommandLineArgs(argc, argv)};
	
	bool pass {true};

	// NOTE: cambered series not formally tested (results are +/- fine)

	// input testing

	// the loop should finish by itself i.e. all exceptions should be caught
	for (std::size_t i {0}; i < 250; i++)
	{
		int type {test::randomInt(1, 5)};

		Stringmap input {constructInput(type)};
		if (output)
			test::echo
			(
				"Input test: ", i, '\n',
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
		// upper side leading edge to trailing edge first
		// then lower side leading edge to trailing edge
		// note: leading edge is repeated!
	Vectorpair<double> profile;
	std::vector<Stringmap> inputs;
	std::vector<geometry::NacaProfileGenerator> generators;

	// build inputs
	inputs.push_back
	(
		Stringmap
		{
			{"series", "0020-63"},
			{"numberOfPoints", "11"},
			{"spacingType", "linear"}
		}
	);
	inputs.push_back
	(
		Stringmap
		{
			{"series", "0020-63"},
			{"numberOfPoints", "11"}
		}
	);
	inputs.push_back
	(
		Stringmap
		{
			{"series", "0012-63"},
			{"numberOfPoints", "11"},
			{"spacingType", "linear"}
		}
	);

	// build generators
	for (auto i : inputs)
	{
		generators.push_back
		(
			geometry::NacaProfileGenerator {i}
		);
	}

	for (auto g : generators)
	{
		// should be empty
		test::compareTest
		(
			pass,
			g.isEmpty(),
			output,
			"Checking if empty"
		);

		// generate profiles
		g.generate();

		// should be full
		test::compareTest
		(
			pass,
			!g.isEmpty(),
			output,
			"Checking if full"
		);

		// check points
		test::compareTest
		(
			pass,
			(
				g.getSize() == 11
			),
			output,
			"Checking size"
		);

		// check results
		profile.clear();

		// upper side first
		for (int i {0}; i < g.getSize(); i++)
			profile.push_back(g.getUpperAt(i));
		// then lower side
		for (int i {0}; i < g.getSize(); i++)
			profile.push_back(g.getLowerAt(i));

		// compare (very dumb but whatever)
		test::compareTest
		(
			pass,
			(
				compareVectorpairs(profile, NACA_0020_LINEAR) ||
				compareVectorpairs(profile, NACA_0020_COSINE) ||
				compareVectorpairs(profile, NACA_0012_LINEAR)
			),
			output,
			"Checking results"
		);
		
		if (output)
			printVectorpair(profile);
	}

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

