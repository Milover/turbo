/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceReferenceLengthScaleRatio

Description
	Class TurbulenceReferenceLengthScaleRatio.

	Expressed as percent of chord.

	Defaults to 0.1.

SourceFiles
	TurbulenceReferenceLengthScaleRatio.cpp


\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_REFERENCE_LENGTH_SCALE_RATIO_H
#define INPUT_TURBULENCE_REFERENCE_LENGTH_SCALE_RATIO_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
			Class TurbulenceReferenceLengthScaleRatio Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceReferenceLengthScaleRatio final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"TurbulenceReferenceLengthScaleRatio"};


	// Constructors

		//- Default constructor
		TurbulenceReferenceLengthScaleRatio() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceReferenceLengthScaleRatio(const Float f);


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
