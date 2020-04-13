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

#include "General.h"
#include "Utility.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	[[maybe_unused]] bool output {test::parseCommandLineArgs(argc, argv)};
	test::initialize("test", false);
	bool pass {true};

	std::vector<Vector> v;

	// default constructor
	v.push_back(Vector {});

	v[0].x() = 1;
	v[0].y() = 0;
	v[0].z() = 0;

	// construct from components
	v.push_back(Vector {1.0, 0.0});

	// construct copy
	v.push_back(Vector {v[1]});

	// move construct
	Vector tmp {1.0, 0.0};
	v.push_back(Vector {std::move(tmp)});

	// test
	for (auto& vec : v)
	{
		if
		(
			vec != Vector {1.0, 0.0}
		)
			pass = false;
	}

	// test mag()
	if
	(
		!isEqual
		(
			mag(Vector {10.0, 0.0}), 10.0
		)
	)
		pass = false;
	
	// test unit()
	if
	(
		unit(Vector {10.0, 0.0}) != Vector {1.0, 0.0}
	)
		pass = false;

	// test dot()
	if
	(
		!isEqual
		(
			dot(Vector {10.0, 0.0}, Vector {1.0, 0.0}), 10.0
		)
	)
		pass = false;

	// test cross()
	Vector v2 {1.0, 2.0, 3.0};
	Vector v3 {3.0, 2.0, 1.0};

	Vector v4 {cross(v2, v3)};

	if
	(
		v4 != Vector {-4.0, 8.0, -4.0}
	)
		pass = false;

	// test member operators
	
	// =
	v2 = v3;
	if
	(
		v2 != Vector {3.0, 2.0, 1.0}
	)
		pass = false;
	
	// +
	v2 = v2 + v3;
	if
	(
		v2 != Vector {6.0, 4.0, 2.0}
	)
		pass = false;
	
	// +
	v2 = +v3;
	if
	(
		v2 != Vector {3.0, 2.0, 1.0}
	)
		pass = false;

	// +=
	v2 += v3;
	if
	(
		v2 != Vector {6.0, 4.0, 2.0}
	)
		pass = false;

	// -
	v2 = v2 - v3;
	if
	(
		v2 != Vector {3.0, 2.0, 1.0}
	)
		pass = false;

	// -
	v3 = -v3;
	if
	(
		v3 != Vector {-3.0, -2.0, -1.0}
	)
		pass = false;

	// -=
	v3 -= v2;
	if
	(
		v3 != Vector {-6.0, -4.0, -2.0}
	)
		pass = false;
	
	// *
	v3 = v3 * 2.0;
	if
	(
		v3 != Vector {-12.0, -8.0, -4.0}
	)
		pass = false;

	// *=
	v3 *= 0.5;
	if
	(
		v3 != Vector {-6.0, -4.0, -2.0}
	)
		pass = false;

	// /
	v3 = v3 / 2.0;
	if
	(
		v3 != Vector {-3.0, -2.0, -1.0}
	)
		pass = false;

	v3 /= 2.0;
	if
	(
		v3 != Vector {-1.5, -1.0, -0.5}
	)
		pass = false;

	// test pass or fail
	if (pass)
		test::echo(1);
	else
		test::echo(0);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
