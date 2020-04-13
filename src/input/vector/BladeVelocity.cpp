/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "BladeVelocity.h"

#include "InitialDesign.h"
#include "Radius.h"
#include "Rps.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BladeVelocity::BladeVelocity(const Vector& v)
:
	RegBase {v}
{}


BladeVelocity::BladeVelocity
(
	const Rps& rps,
	const Radius& r
)
:
	BladeVelocity
	{
		compute::computeBladeVelocity
		(
			rps.value(),
			r.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
