/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "NumberOfStations.h"

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void NumberOfStations::check() const noexcept(ndebug)
{
	if (this->value_ % 2 == 0)
		error(FUNC_INFO, "number of stations must be an odd number");
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

NumberOfStations::NumberOfStations() noexcept
:
	PVBase {1}
{}


NumberOfStations::NumberOfStations(const Integer i)
:
	PVBase {i}
{
	this->check();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
