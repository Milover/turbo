/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing List class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "General.h"
#include "List.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// basic construction
	List<Float>  lFloat {0.0, 1.0, 2.0};
	List<Vector> lVectr
	{
		Vector::xAxis(),
		Vector::yAxis(),
		Vector::zAxis()
	};

	Floatvector vFloatTmp {3.0, 4.0, 5.0};
	std::vector<Vector> vVectrTmp
	{
		Vector::xAxis(),
		Vector::yAxis(),
		Vector::zAxis()
	};

	List<Float>  lFloatTmp {vFloatTmp};
	List<Vector> lVectrTmp {vVectrTmp};

	// append test
	lFloat.append(std::move(vFloatTmp));
	lVectr.append(std::move(vVectrTmp));

	test::compareTest
	(
		pass,
		(
			lFloat == List<Float> {0.0, 1.0, 2.0, 3.0, 4.0, 5.0}
		 && lVectr == List<Vector>
		 {
		 	Vector {1, 0},
		 	Vector {0, 1},
		 	Vector {0, 0, 1},
		 	Vector {1, 0},
		 	Vector {0, 1},
		 	Vector {0, 0, 1},
		 }
		),
		output,
		"Comparing lists after append"
	);

	// test output
	if (output)
	{
		test::echo("lFloat:\t", lFloat);
		test::echo("lVectr:\t", lVectr);
	}

	// test input		// NOTE: mass tested in StringConverter
	lFloat.clear();
	lVectr.clear();
	std::stringstream ss;

	String fListStr
	{
		"(1 2 3 4)"
	};
	ss << fListStr;
	ss >> lFloat;

	if (output)
		test::echo("lFloat:\t", lFloat);

	ss = std::stringstream {};
	String vListStr
	{
		"("
		"(1 0 0)"
		"(0 1 0)"
		"(0 0 1)"
		")"
	};
	ss << vListStr;
	ss >> lVectr;

	if (output)
		test::echo("lVectr:\t", lVectr);

	test::compareTest
	(
		pass,
		(
			lFloat == List<Float> {1.0, 2.0, 3.0, 4.0}
		 && lVectr == List<Vector>
		 {
		 	Vector {1, 0},
		 	Vector {0, 1},
		 	Vector {0, 0, 1}
		 }
		),
		output,
		"Comparing lists after input"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
