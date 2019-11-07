/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <iostream>

#include "Main.h"
#include "turbo.h"

#include "Point.h"
#include "Line.h"
#include "Airfoil.h"
#include "ProfileGeneratorInterface.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc, char* argv[])
{
	
	// print header
	std::cout << turbo::HEADER;

	// print usage
	std::cout << turbo::USAGE;

	// work
	turbo::turbo();

	return 0;
}


// ************************************************************************* //