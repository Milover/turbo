/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Radius

Description
	Class Radius.

SourceFiles
	Radius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_RADIUS_H
#define INPUT_RADIUS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Radius Declaration
\*---------------------------------------------------------------------------*/

class Radius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Radius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Radius(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
