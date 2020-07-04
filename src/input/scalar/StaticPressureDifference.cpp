/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StaticPressureDifference.h"

#include "BladeEfficiency.h"
#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "OutletVelocity.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

StaticPressureDifference::StaticPressureDifference(const Float f)
:
	PVBase {f}
{}


StaticPressureDifference::StaticPressureDifference
(
	const InletVelocity& c_1,
	const OutletVelocity& c_2,
	const BladeVelocity& U,
	const BladeEfficiency& eta,
	const Density& rho
)
:
	StaticPressureDifference
	{
		compute::computeStaticPressureDifference
		(
			c_1.value(),
			c_2.value(),
			U.value(),
			eta.value(),
			rho.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String StaticPressureDifference::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
