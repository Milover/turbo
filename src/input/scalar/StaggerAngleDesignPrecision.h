/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::StaggerAngleDesignPrecision

Description
	Class StaggerAngleDesignPrecision.

	Angle (rad) used during the pressure maximization step of the Airfoil
	design procedure to increment the stagger angle;

	Defaults to 1e-3.

SourceFiles
	StaggerAngleDesignPrecision.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_STAGGER_ANGLE_DESIGN_PRECISION_H
#define INPUT_STAGGER_ANGLE_DESIGN_PRECISION_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class StaggerAngleDesignPrecision Declaration
\*---------------------------------------------------------------------------*/

class StaggerAngleDesignPrecision final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"StaggerAngleDesignPrecision"};


	// Constructors

		//- Default constructor
		StaggerAngleDesignPrecision() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit StaggerAngleDesignPrecision(const Float f);


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
