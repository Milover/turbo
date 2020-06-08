/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "RootOutletVelocity.h"

#include "Error.h"
#include "General.h"
#include "HubRadius.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "Rps.h"
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
	const Rps& N,
	const HubRadius& r_h
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
				N.value(),
				r_h.value()
			),
			N.value(),
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
