/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::HubSkewAngle

Description
	Class HubSkewAngle.

	Defaults to 0.0.

SourceFiles
	HubSkewAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_HUB_SKEW_ANGLE_H
#define INPUT_HUB_SKEW_ANGLE_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class HubSkewAngle Declaration
\*---------------------------------------------------------------------------*/

class HubSkewAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"HubSkewAngle"};


	// Constructors

		//- Default constructor
		HubSkewAngle() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit HubSkewAngle(const Float f);


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
