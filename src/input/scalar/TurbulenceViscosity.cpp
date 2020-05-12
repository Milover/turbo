/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceViscosity.h"

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

TurbulenceViscosity::TurbulenceViscosity(const Float f)
:
	PVBase {f}
{}


TurbulenceViscosity::TurbulenceViscosity
(
	const TurbulenceKineticEnergy& k,
	const TurbulenceReferenceLengthScale& L
)
:
	TurbulenceViscosity
	{
		compute::computeTurbulenceViscosity
		(
			k.value(),
			L.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceViscosity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
