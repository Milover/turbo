/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TurbulenceIntensity.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TurbulenceIntensity::TurbulenceIntensity() noexcept
:
	LVBase {0.05}
{}


TurbulenceIntensity::TurbulenceIntensity(const Float f)
:
	LVBase {f}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TurbulenceIntensity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
