/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Testing Registry class basic funtionality.

	Using some registry objects along the way.

\*---------------------------------------------------------------------------*/

#include <utility>

#include "General.h"
#include "InputRegistry.h"
#include "Registry.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

#include "Test.h"

using namespace turbo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{

	bool output {test::parseCommandLineArgs(argc, argv)};
	bool pass {true};

	// construction
	input::Registry master {};
	input::Registry& slave {master.create()};	// a ref to slave

	// 'master' shouldn't have an owner
	test::compareTest
	(
		pass,
		!master.owner(),
		output,
		"Checking 'master' owner"
	);
	// 'slave' should have an owner and
	// it should be 'master'
	test::compareTest
	(
		pass,
		slave.owner() == &master,
		output,
		"Checking 'slave' owner"
	);

	// store with member-store
	master.store
	(
		input::Rps {50.0}
	);
	slave.store
	(
		input::InclinationAngle			{M_PI}
	);

	// store with global store-all
	input::storeAll
	(
		master,
		input::TotalPressureDifference	{500.0},
		input::VolumeFlowRate			{1.0}
	);
	input::storeAll
	(
		slave,
		input::Radius 					{1.0},
		input::StaggerAngle				{M_PI}
	);

	// check if 'master' stored everything properly
	test::compareTest
	(
		pass,
		(
			// test the keyword version
			master.has(input::Rps::name)
		 && master.has(input::TotalPressureDifference::name)
		 && master.has(input::VolumeFlowRate::name)
			// test the typed version
		 && master.has<input::Rps>()
		 && master.has<input::TotalPressureDifference>()
		 && master.has<input::VolumeFlowRate>()
		),
		output,
		"Checking 'master' variables"
	);

	// check if 'slave' stored everything properly
	test::compareTest
	(
		pass,
		(
			// test the keyword version
			slave.has<NoRecurse>(input::InclinationAngle::name)
		 && slave.has<NoRecurse>(input::Radius::name)
		 && slave.has<NoRecurse>(input::StaggerAngle::name)
			// test the typed version
		 && slave.has<input::InclinationAngle, NoRecurse>()
		 && slave.has<input::Radius, NoRecurse>()
		 && slave.has<input::StaggerAngle, NoRecurse>()
		),
		output,
		"Checking 'slave' variables"
	);

	// check if 'slave' has proper access to master
	test::compareTest
	(
		pass,
		(
			// test the keyword version
			slave.has(input::Rps::name)
		 && slave.has(input::TotalPressureDifference::name)
		 && slave.has(input::VolumeFlowRate::name)
			// test the typed version
		 && slave.has<input::Rps>()
		 && slave.has<input::TotalPressureDifference>()
		 && slave.has<input::VolumeFlowRate>()
		),
		output,
		"Checking 'slave' 'master' access"
	);

	// interact with InputRegistry
	input::InputRegistry::store
	(
		HashMap<String>
		{
			{"BladeVelocity",			"0.0 1.0 0.0"},
			{"Chord",					"0.1"},
			{"Density",					"1.22"},
			{"NumberOfBlades",			"6"}
		}
	);

	// let 'master' get stuff first
	master.get<input::Density>();			// stored, return value discarded
	master.get<input::NumberOfBlades>();	// stored, return value discarded

	// try some variables with default values
	master.get<input::IncidenceAngle>();	// stored, return value discarded

	// check if everything was stored properly
	test::compareTest
	(
		pass,
		(
			master.has<input::Density>()
		 && master.has<input::IncidenceAngle>()
		 && master.has<input::NumberOfBlades>()
		),
		output,
		"Checking 'master' local storage from input"
	);

	// 'slave' should have global access
	// to the new variables
	test::compareTest
	(
		pass,
		(
			// doesn't have them locally
			!slave.has<input::Density, NoRecurse>()
		 && !slave.has<input::IncidenceAngle, NoRecurse>()
		 && !slave.has<input::NumberOfBlades, NoRecurse>()
			// but can access them from 'master'
		 && slave.has<input::Density>()
		 && slave.has<input::IncidenceAngle>()
		 && slave.has<input::NumberOfBlades>()
		),
		output,
		"Checking 'slave' global storage access"
	);

	// let 'slave' get some stuff
	slave.get<input::BladeVelocity>();		// stored, return value discarded
	slave.get<input::Chord>();				// stored, return value discarded

	// try some variables with default values
	slave.get<input::Solidity>();			// stored, return value discarded

	// check if everything was stored properly
	test::compareTest
	(
		pass,
		(
			slave.has<input::BladeVelocity, NoRecurse>()
		 && slave.has<input::Solidity, NoRecurse>()
		 && slave.has<input::Chord, NoRecurse>()
		),
		output,
		"Checking 'slave' local storage from input"
	);

	// check through slave if all variables
	// were constructed with proper values
	test::compareTest
	(
		pass,
		(
			isEqual
			(
				slave.cref<input::Rps>().value(),						50.0
			)
		 && isEqual
			(
				slave.cref<input::InclinationAngle>().value(),			M_PI
			)
		 && isEqual
			(
				slave.cref<input::TotalPressureDifference>().value(),	500.0
			)
		 && isEqual
			(
				slave.cref<input::VolumeFlowRate>().value(),			1.0
			)
		 && isEqual
			(
				slave.cref<input::Radius>().value(),					1.0
			)
		 && isEqual
			(
				slave.cref<input::StaggerAngle>().value(),				M_PI
			)
		 && isEqual
			(
				slave.cref<input::Density>().value(),					1.22
			)
		 && slave.cref<input::NumberOfBlades>().value() ==				6
		 && isEqual	// default value
			(
				slave.cref<input::IncidenceAngle>().value(),			0.0
			)
		 && slave.cref<input::BladeVelocity>().value() == Vector		{0.0, 1.0}
		 && isEqual
			(
				slave.cref<input::Chord>().value(),						0.1
			)
		 && isEqual	// default value
			(
				slave.cref<input::Solidity>().value(),					1.0
			)
		),
		output,
		"Checking constructed variable values"
	);

	// change value of a 'master' variable through slave
	slave.ref<input::Rps>().set(100.0);

	// check if the changes occured
	test::compareTest
	(
		pass,
		(
			isEqual
			(
				master.cref<input::Rps>().value(),	100.0
			)
		 && isEqual
			(
				slave.cref<input::Rps>().value(),	100.0
			)
		),
		output,
		"Checking variable change propagation"
	);

	// change value of a 'slave' variable
	slave.ref<input::BladeVelocity>().set
	(
		Vector {1.0, 1.0, 1.0}
	);

	// check if the changes occured
	test::compareTest
	(
		pass,
		slave.cref<input::BladeVelocity>().value() == Vector {1.0, 1.0, 1.0},
		output,
		"Checking local variable change"
	);

	// test pass or fail
	if (pass)
		test::echo(0);
	else
		test::echo(1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
