/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Pitch

Description
	Class Pitch.

SourceFiles
	Pitch.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_PITCH_H
#define INPUT_PITCH_H

#include "General.h"
#include "NumberOfBlades.h"
#include "PositiveValue.h"
#include "Radius.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Pitch Declaration
\*---------------------------------------------------------------------------*/

class Pitch final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Pitch"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Pitch(const Float f);

		//- Compute and construct
		Pitch
		(
			const NumberOfBlades& N_b,
			const Radius& r
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
