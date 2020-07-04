/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngleScalingFactor

Description
	Class CamberAngleScalingFactor.

	Defaults to 1.0.

SourceFiles
	CamberAngleScalingFactor.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_ANGLE_SCALING_FACTOR_H
#define INPUT_CAMBER_ANGLE_SCALING_FACTOR_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class CamberAngleScalingFactor Declaration
\*---------------------------------------------------------------------------*/

class [[deprecated("this will probably be removed in the future")]]
CamberAngleScalingFactor final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"CamberAngleScalingFactor"};


	// Constructors

		//- Default constructor
		CamberAngleScalingFactor() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit CamberAngleScalingFactor(const Float f);


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
