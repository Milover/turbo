/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceSpecificDissipationRate

Description
	Class TurbulenceSpecificDissipationRate

SourceFiles
	TurbulenceSpecificDissipationRate.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_SPECIFIC_DISSIPATION_RATE_H
#define INPUT_TURBULENCE_SPECIFIC_DISSIPATION_RATE_H

#include "General.h"
#include "TurbulenceKineticEnergy.h"
#include "TurbulenceReferenceLengthScale.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceSpecificDissipationRate Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceSpecificDissipationRate final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TurbulenceSpecificDissipationRate"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceSpecificDissipationRate(const Float f);

		//- Compute and construct,
		TurbulenceSpecificDissipationRate
		(
			const TurbulenceKineticEnergy& k,
			const TurbulenceReferenceLengthScale& L
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
