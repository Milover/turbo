/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "InletVelocity.h"

#include "HubRadius.h"
#include "InitialDesign.h"
#include "ShroudRadius.h"
#include "Vector.h"
#include "VolumeFlowRate.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

InletVelocity::InletVelocity(const Vector& v)
:
	RegBase {v}
{}


InletVelocity::InletVelocity
(
	const VolumeFlowRate& Q,
	const HubRadius& r_h,
	const ShroudRadius& r_s
)
:
	InletVelocity
	{
		compute::computeInletVelocity
		(
			Q.value(),
			r_h.value(),
			r_s.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
