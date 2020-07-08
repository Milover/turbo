/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngleRelDesignPrecision

Description
	Class CamberAngleRelDesignPrecision.

	Percent of initial camber angle (rad) used during the design process
	to increment the camber angle.

	Defaults to 0.05.

SourceFiles
	CamberAngleRelDesignPrecision.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_REL_ANGLE_DESIGN_PRECISION_H
#define INPUT_CAMBER_REL_ANGLE_DESIGN_PRECISION_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class CamberAngleRelDesignPrecision Declaration
\*---------------------------------------------------------------------------*/

class CamberAngleRelDesignPrecision final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"CamberAngleRelDesignPrecision"};


	// Constructors

		//- Default constructor
		CamberAngleRelDesignPrecision() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit CamberAngleRelDesignPrecision(const Float f);


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
