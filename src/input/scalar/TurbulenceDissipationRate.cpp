/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceDissipationRate.h"

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

TurbulenceDissipationRate::TurbulenceDissipationRate(const Float f)
:
	PVBase {f}
{}


TurbulenceDissipationRate::TurbulenceDissipationRate
(
	const TurbulenceKineticEnergy& k,
	const TurbulenceReferenceLengthScale& L
)
:
	TurbulenceDissipationRate
	{
		compute::computeTurbulenceDissipationRate
		(
			k.value(),
			L.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceDissipationRate::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
