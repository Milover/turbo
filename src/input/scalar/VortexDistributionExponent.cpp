/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "VortexDistributionExponent.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

VortexDistributionExponent::VortexDistributionExponent() noexcept
:
	LVBase {-1.0}
{}


VortexDistributionExponent::VortexDistributionExponent(const Float f)
:
	LVBase {f}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String VortexDistributionExponent::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
