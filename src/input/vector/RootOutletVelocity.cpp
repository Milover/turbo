/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "RootOutletVelocity.h"

#include "Density.h"
#include "Error.h"
#include "General.h"
#include "HubRadius.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "Rps.h"
#include "StaticPressureDifference.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

RootOutletVelocity::RootOutletVelocity(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}

//- Compute and construct
RootOutletVelocity::RootOutletVelocity
(
	const InletVelocity& c_1,
	const StaticPressureDifference& dp,
	const Rps& rps,
	const HubRadius& r_h,
	const Density& rho
) noexcept(ndebug)
:
	RootOutletVelocity
	{
		compute::deHaller
		(
			c_1.value(),
			compute::computeRootOutletVelocity
			(
				c_1.value(),
				dp.value(),
				rps.value(),
				r_h.value(),
				rho.value()
			),
			rps.value(),
			r_h.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String RootOutletVelocity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
