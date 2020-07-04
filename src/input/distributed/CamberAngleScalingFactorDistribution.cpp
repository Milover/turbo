/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "CamberAngleScalingFactorDistribution.h"

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CamberAngleScalingFactorDistribution::
CamberAngleScalingFactorDistribution() noexcept
:
	DVBase {1.0}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String CamberAngleScalingFactorDistribution::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
