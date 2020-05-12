/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceKineticEnergy.h"

#include "BladeVelocity.h"
#include "ComputeGeneral.h"
#include "General.h"
#include "InletVelocity.h"
#include "TurbulenceIntensity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TurbulenceKineticEnergy::TurbulenceKineticEnergy(const Float f)
:
	PVBase {f}
{}


TurbulenceKineticEnergy::TurbulenceKineticEnergy
(
	const InletVelocity& c_1,
	const TurbulenceIntensity& I
)
:
	TurbulenceKineticEnergy
	{
		compute::computeTurbulenceKineticEnergy
		(
			c_1.value(),
			I.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceKineticEnergy::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
