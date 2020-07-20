/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "HubRadius.h"

#include "BladeEfficiency.h"
#include "Density.h"
#include "General.h"
#include "RootOutletVelocity.h"
#include "Rps.h"
#include "ShroudRadius.h"
#include "TargetStaticPressureDifference.h"
#include "VortexDistributionExponent.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

HubRadius::HubRadius(const Float f)
:
	PVBase {f}
{}


HubRadius::HubRadius
(
	const RootOutletVelocity& c_2_h,
	const TargetStaticPressureDifference& dp_req,
	const BladeEfficiency& eta,
	const Rps& rps,
	const VortexDistributionExponent& n,
	const ShroudRadius& r_s,
	const Density& rho
)
:
	HubRadius
	{
		compute::computeHubRadius
		(
			c_2_h.value(),
			dp_req.value(),
			eta.value(),
			rps.value(),
			n.value(),
			r_s.value(),
			rho.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String HubRadius::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
