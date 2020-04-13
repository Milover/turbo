/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "CircularArcCamber.h"

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Float CircularArcCamber::computeY(const Float x) const noexcept
{
	Float root
	{
		std::pow(yOffset_, 2) + x - std::pow(x, 2)
	};

	return std::sqrt(root) + yOffset_;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CircularArcCamber::CircularArcCamber(const input::CamberAngle& camber)
:
	CamberGeneratorBase {camber},
	yOffset_
	{
		-0.5 / std::tan(0.5 * camber_.value())
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float CircularArcCamber::inclination(const Float x) const
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		THROW_DOMAIN_ERROR("x out of range [0, 1]");

	Float root
	{
		std::pow(yOffset_, 2) + x - std::pow(x, 2)
	};
	Float dydx
	{
		0.5 * (1.0 - 2.0 * x) / std::sqrt(root)
	};

	return std::atan(dydx);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
