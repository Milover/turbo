/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "ComponentBase.h"
#include "McKenzieDeviation.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double McKenzieDeviation::compute(const ComponentBase& component) const
{
	double sigma {component.get("solidity")};
	double theta
	{
		component.get("bladeInletAngle") - component.get("bladeOutletAngle")
	};

	if (component.get("hubShroudRatio") > 0.8)
		return (2.0 + theta / 3.0) * std::cbrt(1.0 / sigma);

	return (1.1 + 0.31 * theta) * std::cbrt(1.0 / sigma);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
