/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::NumberOfBlades

Description
	Class NumberOfBlades.

SourceFiles
	NumberOfBlades.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_NUMBER_OF_BLADES_H
#define INPUT_NUMBER_OF_BLADES_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class NumberOfBlades Declaration
\*---------------------------------------------------------------------------*/

class NumberOfBlades final
:
	public PositiveValue<Integer>
{
public:

	// Public static data

		inline static const String name {"NumberOfBlades"};


	// Constructors

		//- Construct from a Integer,
		//  no aditional checking required
		explicit NumberOfBlades(const Integer i);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
