/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing InputRegistry class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <utility>
#include <sstream>
#include <fstream>

#include "General.h"
#include "CsvReader.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	[[maybe_unused]] bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	String fakeTabFile
	{
R"(
# comment
0.0		1.0		2.0
0.1		1.1		2.1
0.2		1.2		2.2
)"
	};
	String fakeCommaFile
	{
R"(
# comment
(0 0 0),	(1 0 0),	(2 0 0)
# comment
(0 1 0),	(1 1 0),	(2 1 0)
# comment
(0 2 0),	(1 2 0),	(2 2 0)
# comment
)"
	};
	String fieldMinMaxFile // actual foam postprocessing output, don't change
	{
R"(
# Field minima and maxima
# Time              	field               	min                 	location(min)       	processor           	max                 	location(max)       	processor           
10                  	p                   	-6.451137314219e+02	(-1.167871750250e-01 2.309251689032e-02 5.750000000000e-01)	0	3.272880000000e+00	(1.204163200701e-01 4.110893036542e-02 5.750000000000e-01)	0
)"
	};

	std::stringstream ssTab;
	std::stringstream ssComma;
	std::stringstream ssFoam;

	ssTab << fakeTabFile;
	ssComma << fakeCommaFile;
	ssFoam << fieldMinMaxFile;

	input::CsvReader<Float, Float, Float> csvFloat {'\t', '#'};
	input::CsvReader<Vector, Vector, Vector> csvVector {',', '#'};
	input::CsvReader
	<
		Float,
		String,
		Float,
		Vector,
		Integer,
		Float,
		Vector,
		Integer
	> csvFoam {'\t', '#'};

	csvFloat.read(ssTab);
	csvVector.read(ssComma);
	csvFoam.read(ssFoam);

	auto& vFloat_0 {csvFloat.cref<0>()};
	auto& vFloat_1 {csvFloat.cref<1>()};
	auto& vFloat_2 {csvFloat.cref<2>()};

	auto& vVector_0 {csvVector.cref<0>()};
	auto& vVector_1 {csvVector.cref<1>()};
	auto& vVector_2 {csvVector.cref<2>()};

	test::compareTest
	(
		pass,
		(
			isEqual(vFloat_0[0], 0.0)
		 && isEqual(vFloat_0[1], 0.1)
		 && isEqual(vFloat_0[2], 0.2)
		 && isEqual(vFloat_1[0], 1.0)
		 && isEqual(vFloat_1[1], 1.1)
		 && isEqual(vFloat_1[2], 1.2)
		 && isEqual(vFloat_2[0], 2.0)
		 && isEqual(vFloat_2[1], 2.1)
		 && isEqual(vFloat_2[2], 2.2)
		),
		output,
		"Checking float values"
	);

	test::compareTest
	(
		pass,
		(
			vVector_0[0] == Vector {0, 0, 0}
		 && vVector_0[1] == Vector {0, 1, 0}
		 && vVector_0[2] == Vector {0, 2, 0}
		 && vVector_1[0] == Vector {1, 0, 0}
		 && vVector_1[1] == Vector {1, 1, 0}
		 && vVector_1[2] == Vector {1, 2, 0}
		 && vVector_2[0] == Vector {2, 0, 0}
		 && vVector_2[1] == Vector {2, 1, 0}
		 && vVector_2[2] == Vector {2, 2, 0}
		),
		output,
		"Checking vector values"
	);

	test::compareTest
	(
		pass,
		(
			isEqual(csvFoam.cref<0>().front(), 10.0)
		 && csvFoam.cref<1>().front() == "p"
		 && isEqual(csvFoam.cref<2>().front(), -6.451137314219e+02)
		 && (
		 		csvFoam.cref<3>().front()
			 == Vector {-1.167871750250e-01, 2.309251689032e-02, 0.575}
			)
		 && csvFoam.cref<4>().front() == 0
		 && isEqual(csvFoam.cref<5>().front(), 3.27288)
		 && (
		 		csvFoam.cref<6>().front()
			 == Vector {1.204163200701e-01, 4.110893036542e-02, 0.575}
			)
		 && csvFoam.cref<7>().front() == 0
		),
		output,
		"Checking realistic output"
	);

	csvFloat.clear();
	csvVector.clear();
	csvFoam.clear();

	test::compareTest
	(
		pass,
		(
			csvFloat.cref<0>().empty()
		 && csvFloat.cref<1>().empty()
		 && csvFloat.cref<2>().empty()
		 //
		 && csvVector.cref<0>().empty()
		 && csvVector.cref<1>().empty()
		 && csvVector.cref<2>().empty()
		 //
		 && csvFoam.cref<0>().empty()
		 && csvFoam.cref<1>().empty()
		 && csvFoam.cref<2>().empty()
		 && csvFoam.cref<3>().empty()
		 && csvFoam.cref<4>().empty()
		 && csvFoam.cref<5>().empty()
		 && csvFoam.cref<6>().empty()
		 && csvFoam.cref<7>().empty()
		),
		output,
		"Checking if cleared"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
