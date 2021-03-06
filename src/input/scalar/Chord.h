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
#include "Pitch.h"
#include "PositiveValue.h"
#include "Radius.h"
#include "Solidity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class Solidity;

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
			const Pitch& l,
			const Solidity& sigma
		);

		//- Compute and construct
		Chord
		(
			const NumberOfBlades& N_b,
			const Radius& r,
			const Solidity& sigma
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
