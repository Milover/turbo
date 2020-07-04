/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TargetTotalPressureDifference

Description
	Class TargetTotalPressureDifference.

SourceFiles
	TargetTotalPressureDifference.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TARGET_TOTAL_PRESSURE_DIFFERENCE_H
#define INPUT_TARGET_TOTAL_PRESSURE_DIFFERENCE_H

#include "BladeEfficiency.h"
#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "PositiveValue.h"
#include "OutletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class OutletVelocity;

/*---------------------------------------------------------------------------*\
				Class TargetTotalPressureDifference Declaration
\*---------------------------------------------------------------------------*/

class TargetTotalPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TargetTotalPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TargetTotalPressureDifference(const Float f);

		//- Compute and construct
		TargetTotalPressureDifference
		(
			const OutletVelocity& c_2,
			const BladeVelocity& U,
			const BladeEfficiency& eta,
			const Density& rho
		);


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
