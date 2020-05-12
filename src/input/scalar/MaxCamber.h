/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxCamber

Description
	Class MaxCamber.

SourceFiles
	MaxCamber.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_CAMBER_H
#define INPUT_MAX_CAMBER_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class MaxCamber Declaration
\*---------------------------------------------------------------------------*/

class MaxCamber final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"MaxCamber"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit MaxCamber(const Float f);


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
