/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>

#include "Naca4DigitDistribution.h"
#include "InputObjectBase.h"
#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Naca4DigitDistribution::scaleCoefficients()
{
	for (auto& a : a_)
		a *= scale_ * get("maxThickness");
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Naca4DigitDistribution::buildInputMap() noexcept
{
	store("maxThickness", NAN);	// [-] - % of chord
}


void Naca4DigitDistribution::check() const
{
	if
	(
		!isInRange(get("maxThickness"), 0.0, 1.0)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxThickness' out of range [0, 1]");
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca4DigitDistribution::Naca4DigitDistribution
(
	const Stringmap<>& input
)
:
	a_
	{
		0.2969,
	   -0.1260,
	   -0.3516,
		0.2843,
	   -0.1015
	}
{
	buildInputMap();
	parse(input);
	check();

	scaleCoefficients();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Naca4DigitDistribution::getThicknessAt(const double x) const noexcept
{
	return a_[0] * std::sqrt(x) +
		   a_[1] * x +
		   a_[2] * std::pow(x, 2) +
		   a_[3] * std::pow(x, 3) +
		   a_[4] * std::pow(x, 4);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
