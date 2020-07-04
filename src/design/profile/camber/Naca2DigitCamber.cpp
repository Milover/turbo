/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "Naca2DigitCamber.h"

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Float Naca2DigitCamber::computeMaxCamber() noexcept
{
	Float root
	{
		0.25 / std::pow(std::tan(camber_.value()), 2)
	  + pos_.value() * (1.0 - pos_.value())
	};

	return -0.25 / std::tan(camber_.value()) + 0.5 * std::sqrt(root);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Float Naca2DigitCamber::computeY(const Float x) const noexcept
{
	if (x < pos_.value())
		return max_.value() / std::pow(pos_.value(), 2) *
			(
				2.0 * pos_.value() * x - std::pow(x, 2)
			);
	else
		return max_.value() / std::pow(1.0 - pos_.value(), 2) *
			(
				1.0 + 2.0 * pos_.value() * (x - 1.0) - std::pow(x, 2)
			);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca2DigitCamber::Naca2DigitCamber(const input::Registry& reg)
:
	CamberGeneratorBase {reg},
	pos_
	{
		reg.cref<input::MaxCamberPosition>()
	},
	max_ {computeMaxCamber()}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Naca2DigitCamber::inclination(const Float x) const noexcept(ndebug)
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		error(FUNC_INFO, x, " out of range [0, 1.0]");

	Float dydx;

	if (x < pos_.value())
		dydx = 2.0 * max_.value()
			 / std::pow(pos_.value(), 2)
			 * (pos_.value() - x);
	else
		dydx = 2.0 * max_.value()
			 / std::pow(1.0 - pos_.value(), 2)
			 * (pos_.value() - x);

	return std::atan(dydx);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
