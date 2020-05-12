/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "BladeVelocity.h"

#include "Error.h"
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

BladeVelocity::BladeVelocity(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


BladeVelocity::BladeVelocity
(
	const Rps& rps,
	const Radius& r
) noexcept(ndebug)
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


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String BladeVelocity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
