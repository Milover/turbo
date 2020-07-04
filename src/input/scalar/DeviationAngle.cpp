/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "DeviationAngle.h"

#include "BladeVelocity.h"
#include "ComputeDesign.h"
#include "General.h"
#include "OutletVelocity.h"
#include "OutletRelativeVelocity.h"
#include "Utility.h"
#include "Vector.h"

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


DeviationAngle::DeviationAngle
(
	const OutletVelocity& c_2,
	const BladeVelocity& U,
	const OutletRelativeVelocity& w_2_real
)
:
	DeviationAngle
	{
		compute::computeDeviationAngle
		(
			c_2.value(),
			U.value(),
			w_2_real.value()
		)
	}
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
