/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::DesignPressureRelTolerance

Description
	Class DesignPressureRelTolerance.

	Relative difference (tolerance) between the target and achieved total
	pressure.

	Defaults to 0.025.

SourceFiles
	DesignPressureRelTolerance.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_DESIGN_PRESSURE_REL_TOLERANCE_H
#define INPUT_DESIGN_PRESSURE_REL_TOLERANCE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class DesignPressureRelTolerance Declaration
\*---------------------------------------------------------------------------*/

class DesignPressureRelTolerance final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"DesignPressureRelTolerance"};


	// Constructors

		//- Default constructor
		DesignPressureRelTolerance() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit DesignPressureRelTolerance(const Float f);


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
