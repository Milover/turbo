/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "CamberAngle.h"

#include "BladeVelocity.h"
#include "CamberAngleScalingFactor.h"
#include "General.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "OutletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CamberAngle::CamberAngle(const Float f)
:
	RegBase {f}
{}


CamberAngle::CamberAngle
(
	const InletVelocity& c_1,
	const OutletVelocity& c_2,
	const BladeVelocity& U,
	const CamberAngleScalingFactor& coeff
)
:
	CamberAngle
	{
		compute::computeCamberAngle
		(
			c_1.value(),
			c_2.value(),
			U.value(),
			coeff.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String CamberAngle::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
