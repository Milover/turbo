/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "DeviationAngle.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

DeviationAngle::DeviationAngle() noexcept
:
	RegBase {0.0}
{}


DeviationAngle::DeviationAngle(const Float f)
:
	RegBase {f}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String DeviationAngle::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
