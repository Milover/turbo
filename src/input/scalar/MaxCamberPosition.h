/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxCamberPosition

Description
	Class MaxCamberPosition.

SourceFiles
	MaxCamberPosition.cpp

	Defaults to 0.4.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_CAMBER_POSITION_H
#define INPUT_MAX_CAMBER_POSITION_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class MaxCamberPosition Declaration
\*---------------------------------------------------------------------------*/

class MaxCamberPosition final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"MaxCamberPosition"};


	// Constructors

		//- Default constructor
		MaxCamberPosition() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit MaxCamberPosition(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
