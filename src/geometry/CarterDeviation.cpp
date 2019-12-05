/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "ComponentBase.h"
#include "CarterDeviation.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double CarterDeviation::compute(const ComponentBase& component) const
{
	double beta_2 {component.get("fluidOutletAngle")};
	double pos {component.get("maxCamberPosition")};
	double sigma {component.get("solidity")};
	double theta
	{
		component.get("bladeInletAngle") - component.get("bladeOutletAngle")
	};

	double m
	{
		0.23 * std::pow((2.0 * pos) , 2) + 0.002 * beta_2
	};

	return m * theta / std::sqrt(sigma);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
