/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TargetTotalPressureDifference.h"

#include "BladeEfficiency.h"
#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "InitialDesign.h"
#include "OutletVelocity.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TargetTotalPressureDifference::TargetTotalPressureDifference(const Float f)
:
	PVBase {f}
{}


TargetTotalPressureDifference::TargetTotalPressureDifference
(
	const OutletVelocity& c_2,
	const BladeVelocity& U,
	const BladeEfficiency& eta,
	const Density& rho
)
:
	TargetTotalPressureDifference
	{
		compute::computeTargetTotalPressureDifference
		(
			c_2.value(),
			U.value(),
			eta.value(),
			rho.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TargetTotalPressureDifference::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
