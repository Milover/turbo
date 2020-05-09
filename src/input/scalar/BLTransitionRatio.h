/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BLTransitionRatio

Description
	Class BLTransitionRatio.

	Ratio of the last boundary layer cell height to the first outer mesh
	cell height.

	Defaults to 0.75.

SourceFiles
	BLTransitionRatio.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BL_TRANSITION_RATIO_H
#define INPUT_BL_TRANSITION_RATIO_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class BLTransitionRatio Declaration
\*---------------------------------------------------------------------------*/

class BLTransitionRatio final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"BLTransitionRatio"};


	// Constructors

		//- Default constructor
		BLTransitionRatio() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit BLTransitionRatio(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
