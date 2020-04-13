/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <iostream>

#include "Main.h"

#include "turbo.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int main(int argc [[maybe_unused]], char* argv[] [[maybe_unused]])
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
