/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "OutletRelativeVelocity.h"

#include "Error.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

OutletRelativeVelocity::OutletRelativeVelocity(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String OutletRelativeVelocity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
