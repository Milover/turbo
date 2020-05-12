/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceReferenceLengthScale.h"

#include "Chord.h"
#include "General.h"
#include "TurbulenceReferenceLengthScaleRatio.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TurbulenceReferenceLengthScale::TurbulenceReferenceLengthScale(const Float f)
:
	PVBase {f}
{}


TurbulenceReferenceLengthScale::TurbulenceReferenceLengthScale
(
	const Chord& c,
	const TurbulenceReferenceLengthScaleRatio& L_r
)
:
	TurbulenceReferenceLengthScale
	{
		c.value() * L_r.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceReferenceLengthScale::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
