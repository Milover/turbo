/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "NumberOfCamberPoints.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

NumberOfCamberPoints::NumberOfCamberPoints() noexcept
:
	PVBase {150}
{}


NumberOfCamberPoints::NumberOfCamberPoints(const Integer i)
:
	PVBase {i}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String NumberOfCamberPoints::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
