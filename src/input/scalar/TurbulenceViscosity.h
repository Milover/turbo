/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceViscosity

Description
	Class TurbulenceViscosity

SourceFiles
	TurbulenceViscosity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_VISCOSITY_H
#define INPUT_TURBULENCE_VISCOSITY_H

#include "General.h"
#include "TurbulenceKineticEnergy.h"
#include "TurbulenceReferenceLengthScale.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceViscosity Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceViscosity final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TurbulenceViscosity"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceViscosity(const Float f);

		//- Compute and construct,
		TurbulenceViscosity
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
