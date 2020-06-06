/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Solidity.h"

#include "Chord.h"
#include "General.h"
#include "Pitch.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Solidity::Solidity() noexcept
:
	PVBase {1.0}
{}


Solidity::Solidity(const Float f)
:
	PVBase {f}
{}


Solidity::Solidity
(
	const Chord& c,
	const Pitch& l
)
:
	Solidity
	{
		c.value() / l.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String Solidity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
