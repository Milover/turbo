/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "NoCamber.h"

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "Registry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Float NoCamber::computeY(const Float x [[maybe_unused]]) const noexcept
{
	return 0.0;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

NoCamber::NoCamber(const input::Registry& reg)
:
	CamberGeneratorBase {reg}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float NoCamber::inclination(const Float x) const noexcept(ndebug)
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		error(FUNC_INFO, x, " out of range [0, 1]");

	return 0.0;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
