/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Naca2DigitCamber.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Naca2DigitCamber::computeMaxCamber() const noexcept
{
	Float root
	{
		0.25 / std::pow(std::tan(camber_), 2) +
		maxCamberPosition_ * (1.0 - maxCamberPosition_)
	};

	maxCamber_ = -0.25 / std::tan(camber_) + 0.5 * std::sqrt(root)
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Float Naca2DigitCamber::computeY(const Float x) const
{
	if (x < maxCamberPosition_)
		return maxCamber_ / std::pow(maxCamberPosition_, 2) *
			(
				2.0 * maxCamberPosition_ * x - std::pow(x, 2)
			);
	else
		return maxCamber_ / std::pow((1.0 - maxCamberPosition_), 2) *
			(
				1.0 - 2.0 * maxCamberPosition_ * (1.0 + x) - std::pow(x, 2)
			);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

// TODO: clean up a bit
Naca2DigitCamber::Naca2DigitCamber(const Float camber)
:
	CamberGeneratorBase {camber}
{
	if (inputRegistry::has("maxCamberPosition"))
	{
		maxCamberPosition_ = StringConverter<Float> {}
		(
			InputRegistry::get("maxCamberPosition")
		);

		if
		(
			!isInRange(maxCamberPosition_, 0.0, 1.0)
		)
			THROW_RUNTIME_ERROR("maxCamberPosition out of range [0, 1]");
	}

	computeMaxCamber();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Naca2DigitCamber::inclination(const Float x) const
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		THROW_DOMAIN_ERROR("x out of range [0, 1.0]");

	Float dydx;

	if (x < maxCamberPosition_)
		dydx = 2.0 * maxCamber_
			 / std::pow(maxCamberPosition_, 2)
			 * (maxCamberPosition_ - x);
	else
		dydx = 2.0 * maxCamber_
			 / std::pow((1.0 - maxCamberPosition_), 2)
			 * (maxCamberPosition_ - x);

	return std::atan(dydx);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
