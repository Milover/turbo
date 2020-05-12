/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "InletRelativeVelocity.h"

#include "BladeVelocity.h"
#include "Error.h"
#include "InletVelocity.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

InletRelativeVelocity::InletRelativeVelocity(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


InletRelativeVelocity::InletRelativeVelocity
(
	const InletVelocity& c_1,
	const BladeVelocity& U
) noexcept(ndebug)
:
	InletRelativeVelocity
	{
		c_1.value() - U.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String InletRelativeVelocity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
