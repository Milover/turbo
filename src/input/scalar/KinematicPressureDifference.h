/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::KinematicPressureDifference

Description
	Class KinematicPressureDifference.

SourceFiles
	KinematicPressureDifference.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_KINEMATIC_PRESSURE_DIFFERENCE_H
#define INPUT_KINEMATIC_PRESSURE_DIFFERENCE_H

#include "Density.h"
#include "General.h"
#include "PositiveValue.h"
#include "StaticPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class KinematicPressureDifference Declaration
\*---------------------------------------------------------------------------*/

class KinematicPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"KinematicPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit KinematicPressureDifference(const Float f);

		//- Compute and construct
		KinematicPressureDifference
		(
			const StaticPressureDifference& dp,
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
