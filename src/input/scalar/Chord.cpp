/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Chord.h"

#include "General.h"
#include "InitialDesign.h"
#include "NumberOfBlades.h"
#include "Pitch.h"
#include "Radius.h"
#include "Solidity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Chord::Chord(const Float f)
:
	PVBase {f}
{}


Chord::Chord
(
	const Pitch& l,
	const Solidity& sigma
)
:
	Chord
	{
		compute::computeChord
		(
			l.value(),
			sigma.value()
		)
	}
{}


Chord::Chord
(
	const NumberOfBlades& N_b,
	const Radius& r,
	const Solidity& sigma
)
:
	Chord
	{
		compute::computeChord
		(
			N_b.value(),
			r.value(),
			sigma.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String Chord::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
