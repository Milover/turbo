/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::HubRadius

Description
	Class HubRadius.

SourceFiles
	HubRadius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_HUB_RADIUS_H
#define INPUT_HUB_RADIUS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class HubRadius Declaration
\*---------------------------------------------------------------------------*/

class HubRadius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"HubRadius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit HubRadius(const Float f);


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
