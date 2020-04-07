/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "DeHaller.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

double DeHaller::operator()
(
	const double fluidInletAngle,
	const double fluidOutletAngle
) const noexcept
{
	double beta1 {degToRad(fluidInletAngle)};
	double beta2 {degToRad(fluidOutletAngle)};
	double beta2New
	{
		std::acos
		(
			std::cos(beta1) / DeHaller::constant
		)
	};

	if (beta2 > beta2New)
		beta2 = beta2New;

	return radToDeg(beta2);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
