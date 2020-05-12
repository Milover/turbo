/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceSpecificDissipationRate.h"

#include "ComputeGeneral.h"
#include "General.h"
#include "TurbulenceKineticEnergy.h"
#include "TurbulenceReferenceLengthScale.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TurbulenceSpecificDissipationRate::TurbulenceSpecificDissipationRate
(
	const Float f
)
:
	PVBase {f}
{}


TurbulenceSpecificDissipationRate::TurbulenceSpecificDissipationRate
(
	const TurbulenceKineticEnergy& k,
	const TurbulenceReferenceLengthScale& L
)
:
	TurbulenceSpecificDissipationRate
	{
		compute::computeTurbulenceSpecificDissipationRate
		(
			k.value(),
			L.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceSpecificDissipationRate::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
