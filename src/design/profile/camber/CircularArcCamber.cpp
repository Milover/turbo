/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "CircularArcCamber.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void CircularArcCamber::buildInputMap() noexcept
{
	store("maxCamberPosition", 0.5);	// [-] - % of chord
}


void CircularArcCamber::computeParameters(const double camberAngle) noexcept
{
	double theta {degToRad(camberAngle)};

	offset_ = -0.5 * chord_ / std::tan(0.5 * theta);

	store
	(
		"maxCamber",
		computeY(get("maxCamberPosition"))
	);
}


double CircularArcCamber::computeY(const double x) const
{
	double root
	{
		std::pow(offset_, 2) + x * chord_ - std::pow(x, 2)
	};

	return std::sqrt(root) + offset_;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CircularArcCamber::CircularArcCamber(const Stringmap<>& input)
:
	CamberGeneratorBase {input}
{
	buildInputMap();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double CircularArcCamber::getInclinationAt(const double x) const
{
	if
	(
		!isInRange(x, 0.0, chord_)
	)
		THROW_DOMAIN_ERROR("x out of range [0, chord]");

	double root
	{
		std::pow(offset_, 2) + x * chord_ - std::pow(x, 2)
	};
	double dydx
	{
		0.5 * (chord_ - 2.0 * x) / std::sqrt(root)
	};

	return radToDeg(std::atan(dydx));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
