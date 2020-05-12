/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceReferenceLengthScale

Description
	Class TurbulenceReferenceLengthScale.

SourceFiles
	TurbulenceReferenceLengthScale.cpp


\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_REFERENCE_LENGTH_SCALE_H
#define INPUT_TURBULENCE_REFERENCE_LENGTH_SCALE_H

#include "Chord.h"
#include "General.h"
#include "PositiveValue.h"
#include "TurbulenceReferenceLengthScaleRatio.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceReferenceLengthScale Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceReferenceLengthScale final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TurbulenceReferenceLengthScale"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceReferenceLengthScale(const Float f);

		//- Compute and construct
		TurbulenceReferenceLengthScale
		(
			const Chord& c,
			const TurbulenceReferenceLengthScaleRatio& L_r
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
