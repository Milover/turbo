/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Chord

Description
	Class Chord.

SourceFiles
	Chord.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CHORD_H
#define INPUT_CHORD_H

#include "General.h"
#include "NumberOfBlades.h"
#include "PositiveValue.h"
#include "Radius.h"
#include "Solidity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Chord Declaration
\*---------------------------------------------------------------------------*/

class Chord final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Chord"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Chord(const Float f);

		//- Compute and construct
		Chord
		(
			const NumberOfBlades& N_b,
			const Radius& r,
			const Solidity& sigma
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
