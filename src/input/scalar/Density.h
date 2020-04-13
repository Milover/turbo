/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Density

Description
	Class Density.

SourceFiles
	Density.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_DENSITY_H
#define INPUT_DENSITY_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Density Declaration
\*---------------------------------------------------------------------------*/

class Density final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Density"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Density(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
