/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxProfileThickness

Description
	Class MaxProfileThickness.

SourceFiles
	MaxProfileThickness.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_PROFILE_THICKNESS_H
#define INPUT_MAX_PROFILE_THICKNESS_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class MaxProfileThickness Declaration
\*---------------------------------------------------------------------------*/

class MaxProfileThickness final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"MaxProfileThickness"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit MaxProfileThickness(const Float f);


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
