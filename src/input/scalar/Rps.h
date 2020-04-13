/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Rps

Description
	Class Rps (revolutions per second).

SourceFiles
	Rps.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_RPS_H
#define INPUT_RPS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Rps Declaration
\*---------------------------------------------------------------------------*/

class Rps final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Rps"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Rps(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
