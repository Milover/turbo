/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Vector class basic funtionality.

\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include <vector>

#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", false);
	bool pass {true};

	std::vector<geometry::Vector> v;

	// default constructor
	v.push_back(geometry::Vector {});

	v[0].x = 1;
	v[0].y = 0;
	v[0].z = 0;

	// construct from components
	v.push_back(geometry::Vector {1, 0});

	// construct copy
	v.push_back(geometry::Vector {v[1]});

	// test
	for (auto vec : v)
	{
		if
		(
			!isEqual(vec.x, 1.0) ||
			!isEqual(vec.y, 0.0) ||
			!isEqual(vec.z, 0.0)
		)
			pass = false;
	}

	// test member functions

	// test getMagnitude()
	geometry::Vector v1 {10, 0, 0};
	if (!isEqual(v1.getMagnitude(), 10.0))
		pass = false;
	
	// test getUnitVector()
	geometry::Vector unitV1 {v1.getUnitVector()};

	if (!isEqual(unitV1.getMagnitude(), 1.0))
		pass = false;
	if
	(
		!isEqual(unitV1.x, 1.0) ||
		!isEqual(unitV1.y, 0.0) ||
		!isEqual(unitV1.z, 0.0)
	)
		pass = false;
	
	// test dot()
	double dotProduct {v1.dot(unitV1)};
	if (!isEqual(dotProduct, 10.0))
		pass = false;
	
	// test ex()
	geometry::Vector v2 {1, 2, 3};
	geometry::Vector v3 {3, 2, 1};

	geometry::Vector v4 {v2.ex(v3)};
	if
	(
		!isEqual(v4.x, -4.0) ||
		!isEqual(v4.y, 8.0) ||
		!isEqual(v4.z, -4.0)
	)
		pass = false;
	
	// test member operators
	
	// =
	v2 = v3;
	if
	(
		!isEqual(v2.x, 3.0) ||
		!isEqual(v2.y, 2.0) ||
		!isEqual(v2.z, 1.0)
	)
		pass = false;
	
	// +
	v2 = v2 + v3;
	if
	(
		!isEqual(v2.x, 6.0) ||
		!isEqual(v2.y, 4.0) ||
		!isEqual(v2.z, 2.0)
	)
		pass = false;
	
	// +
	v2 = +v3;
	if
	(
		!isEqual(v2.x, 3.0) ||
		!isEqual(v2.y, 2.0) ||
		!isEqual(v2.z, 1.0)
	)
		pass = false;

	// +=
	v2 += v3;
	if
	(
		!isEqual(v2.x, 6.0) ||
		!isEqual(v2.y, 4.0) ||
		!isEqual(v2.z, 2.0)
	)
		pass = false;

	// -
	v2 = v2 - v3;
	if
	(
		!isEqual(v2.x, 3.0) ||
		!isEqual(v2.y, 2.0) ||
		!isEqual(v2.z, 1.0)
	)
		pass = false;

	// -
	v3 = -v3;
	if
	(
		!isEqual(v3.x, -3.0) ||
		!isEqual(v3.y, -2.0) ||
		!isEqual(v3.z, -1.0)
	)
		pass = false;

	// -=
	v3 -= v2;
	if
	(
		!isEqual(v3.x, -6.0) ||
		!isEqual(v3.y, -4.0) ||
		!isEqual(v3.z, -2.0)
	)
		pass = false;
	
	// *
	v3 = v3 * 2.0;
	if
	(
		!isEqual(v3.x, -12.0) ||
		!isEqual(v3.y, -8.0) ||
		!isEqual(v3.z, -4.0)
	)
		pass = false;

	// *=
	v3 *= 0.5;
	if
	(
		!isEqual(v3.x, -6.0) ||
		!isEqual(v3.y, -4.0) ||
		!isEqual(v3.z, -2.0)
	)
		pass = false;

	// /
	v3 = v3 / 2.0;
	if
	(
		!isEqual(v3.x, -3.0) ||
		!isEqual(v3.y, -2.0) ||
		!isEqual(v3.z, -1.0)
	)
		pass = false;

	// divide by 0
	try
	{
		v3 = v3 / 0.0;
	}
	catch (std::invalid_argument& e)
	{}

	v3 /= 2.0;
	if
	(
		!isEqual(v3.x, -1.5) ||
		!isEqual(v3.y, -1.0) ||
		!isEqual(v3.z, -0.5)
	)
		pass = false;
	
	// test comparisons
	geometry::Vector v5 {1, 0 ,0};
	geometry::Vector v6 {1, 0 ,0};
	geometry::Vector v7 {0, 1 ,0};

	// should be equal
	test::compareTest
	(
		pass,
		(v5 == v6),
		output,
		"Checking if equal"
	);

	// should not be equal
	test::compareTest
	(
		pass,
		(v5 != v7),
		output,
		"Checking if not equal"
	);

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
