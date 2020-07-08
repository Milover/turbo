/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::StaggerAngleRelDesignPrecision

Description
	Class StaggerAngleRelDesignPrecision.

	Percent of initial stagger angle (rad) used during the design process
	to increment the stagger angle.

	Defaults to 0.05.

SourceFiles
	StaggerAngleRelDesignPrecision.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_STAGGER_ANGLE_REL_DESIGN_PRECISION_H
#define INPUT_STAGGER_ANGLE_REL_DESIGN_PRECISION_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class StaggerAngleRelDesignPrecision Declaration
\*---------------------------------------------------------------------------*/

class StaggerAngleRelDesignPrecision final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"StaggerAngleRelDesignPrecision"};


	// Constructors

		//- Default constructor
		StaggerAngleRelDesignPrecision() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit StaggerAngleRelDesignPrecision(const Float f);


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
