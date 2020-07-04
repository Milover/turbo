/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "VortexDistributionExponent.h"

#include "BladeEfficiency.h"
#include "Density.h"
#include "General.h"
#include "InitialDesign.h"
#include "HubRadius.h"
#include "RootOutletVelocity.h"
#include "Rps.h"
#include "ShroudRadius.h"
#include "TargetStaticPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

VortexDistributionExponent::VortexDistributionExponent(const Float f)
:
	LVBase {f}
{}

VortexDistributionExponent::VortexDistributionExponent
(
	const RootOutletVelocity& c_2_h,
	const TargetStaticPressureDifference& dp_req,
	const BladeEfficiency& eta,
	const Rps& rps,
	const HubRadius& r_h,
	const ShroudRadius& r_s,
	const Density& rho
)
:
	VortexDistributionExponent
	{
		compute::computeVortexDistributionExponent
		(
			c_2_h.value(),
			dp_req.value(),
			eta.value(),
			rps.value(),
			r_h.value(),
			r_s.value(),
			rho.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String VortexDistributionExponent::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
