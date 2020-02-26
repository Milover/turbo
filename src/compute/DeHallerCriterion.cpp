/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "DeHallerCriterion.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

double DeHallerCriterion::operator()
(
	const double fluidInletAngle,
	const double fluidOutletAngle
) const
{
	double beta1 {degToRad(fluidInletAngle)};
	double beta2 {degToRad(fluidOutletAngle)};
	double beta2New
	{
		std::acos
		(
			std::cos(beta1) / DeHallerCriterion::constant
		)
	};

	if (beta2 > beta2New)
		beta2 = beta2New;

	return radToDeg(beta2);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
