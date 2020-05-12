/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceDissipationRate

Description
	Class TurbulenceDissipationRate

SourceFiles
	TurbulenceDissipationRate.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_DISSIPATION_RATE_H
#define INPUT_TURBULENCE_DISSIPATION_RATE_H

#include "General.h"
#include "TurbulenceKineticEnergy.h"
#include "TurbulenceReferenceLengthScale.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceDissipationRate Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceDissipationRate final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TurbulenceDissipationRate"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceDissipationRate(const Float f);

		//- Compute and construct,
		TurbulenceDissipationRate
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
