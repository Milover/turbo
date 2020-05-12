/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TotalPressureDifference.h"

#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "OutletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TotalPressureDifference::TotalPressureDifference(const Float f)
:
	PVBase {f}
{}


TotalPressureDifference::TotalPressureDifference
(
	const InletVelocity& c_1,
	const OutletVelocity& c_2,
	const BladeVelocity& U,
	const Density& rho
)
:
	TotalPressureDifference
	{
		compute::computeTotalPressureDifference
		(
			c_1.value(),
			c_2.value(),
			U.value(),
			rho.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TotalPressureDifference::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
