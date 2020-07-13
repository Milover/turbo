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
#include "Polyline.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	math::Polyline<Float> p1 {1.0, 2.0, 0.0, 1.0};

	test::echo(std::fixed, std::setprecision(5));
	test::echo("p1[ 0.00]:\t", p1( 0.00));
	test::echo("p1[ 0.25]:\t", p1( 0.25));
	test::echo("p1[ 0.50]:\t", p1( 0.50));
	test::echo("p1[ 0.75]:\t", p1( 0.75));
	test::echo("p1[ 1.00]:\t", p1( 1.00));
	test::echo();
	test::echo("p1[-1.00]:\t", p1(-1.00));
	test::echo("p1[ 2.00]:\t", p1( 2.00));
	test::echo();
	test::echo("p1[ 0.33]:\t", p1(1.0/3.0));
	test::echo("p1[ 0.66]:\t", p1(2.0/3.0));
	test::echo();

	math::Polyline<Float> p2 {1.2, 0.7, 0.5};
	test::echo("p2[0.00]:\t", p2(0.00));
	test::echo("p2[0.25]:\t", p2(0.25));
	test::echo("p2[0.50]:\t", p2(0.50));
	test::echo("p2[0.75]:\t", p2(0.75));
	test::echo("p2[1.00]:\t", p2(1.00));
	test::echo();

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
