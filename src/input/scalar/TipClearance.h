/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TipClearance

Description
	Class TipClearance.

SourceFiles
	TipClearance.cpp

	Defaults to 0.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TIP_CLEARANCE_H
#define INPUT_TIP_CLEARANCE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class TipClearance Declaration
\*---------------------------------------------------------------------------*/

class TipClearance final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TipClearance"};


	// Constructors

		//- Default constructor
		TipClearance() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit TipClearance(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
