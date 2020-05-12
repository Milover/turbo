/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceKineticEnergy

Description
	Class TurbulenceKineticEnergy

SourceFiles
	TurbulenceKineticEnergy.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_KINETIC_ENERGY_H
#define INPUT_TURBULENCE_KINETIC_ENERGY_H

#include "BladeVelocity.h"
#include "General.h"
#include "InletVelocity.h"
#include "TurbulenceIntensity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceKineticEnergy Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceKineticEnergy final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TurbulenceKineticEnergy"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceKineticEnergy(const Float f);

		//- Compute and construct,
		//	NOTE: use absolute inlet velocity
		TurbulenceKineticEnergy
		(
			const InletVelocity& c_1,
			const TurbulenceIntensity& I
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
