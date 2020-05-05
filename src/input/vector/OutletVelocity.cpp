/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "OutletVelocity.h"

#include "BladeVelocity.h"
#include "Error.h"
#include "HubRadius.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "Radius.h"
#include "RootOutletVelocity.h"
#include "Vector.h"
#include "VortexDistributionExponent.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

OutletVelocity::OutletVelocity(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


OutletVelocity::OutletVelocity
(
	const RootOutletVelocity& c_2_h,
	const VortexDistributionExponent& n,
	const Radius& r,
	const HubRadius& r_h
) noexcept(ndebug)
:
	OutletVelocity
	{
		compute::computeVortexDistributionVelocity
		(
			c_2_h.value(),
			n.value(),
			r.value(),
			r_h.value()
		)
	}
{}


OutletVelocity::OutletVelocity
(
	const InletVelocity& c_1,
	const RootOutletVelocity& c_2_h,
	const VortexDistributionExponent& n,
	const Radius& r,
	const HubRadius& r_h,
	const BladeVelocity& U
) noexcept(ndebug)
:
	OutletVelocity
	{
		compute::deHaller
		(
			c_1.value(),
			compute::computeVortexDistributionVelocity
			(
				c_2_h.value(),
				n.value(),
				r.value(),
				r_h.value()
			),
			U.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
