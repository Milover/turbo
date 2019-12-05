/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>

#include "Naca4DigitModifiedDistribution.h"
#include "InputObjectBase.h"
#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Naca4DigitModifiedDistribution::checkMaxThickness() const
{
	if
	(
		!isInRange(get("maxThickness"), 0.0, 1.0)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxThickness' out of range [0, 1]");
}


void Naca4DigitModifiedDistribution::checkMaxThicknessPosition() const
{
	if
	(
		!isInRange(get("maxThicknessPosition"), 0.2, 0.6)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxThicknessPosition' out of range [0.2, 0.6]");
}


void Naca4DigitModifiedDistribution::checkRadiusIndex() const
{
	if
	(
		!isInRange(get("maxThicknessPosition"), 1.0, 9.0)
	)
		THROW_RUNTIME_ERROR("value of keyword 'radiusIndex' out of range [1, 9]");
}


void Naca4DigitModifiedDistribution::computeA0() noexcept
{
	a_[0] = 0.2969 * get("radiusIndex") / 6.0;
}


void Naca4DigitModifiedDistribution::lookUpD1() noexcept
{
	int m
	{
		static_cast<int>(0.5 + 10.0 * get("maxThicknessPosition"))
	};

	d_[1] = d1Table_.find(m)->second;
}


void Naca4DigitModifiedDistribution::computeD2() noexcept
{
	double B {chord_ - get("maxThicknessPosition")};

	d_[2] = ( -3.0 * d_[0] - 2.0 * d_[1] * B + 0.3 ) / std::pow(B, 2);
}


void Naca4DigitModifiedDistribution::computeD3() noexcept
{
	double B {chord_ - get("maxThicknessPosition")};

	d_[3] = ( -d_[1] / std::pow(B, 2) - 2.0 * d_[2] / B ) / 3.0;
}


void Naca4DigitModifiedDistribution::scaleCoefficients()
{
	for (auto& a : a_)
		a *= scale_ * get("maxThickness");

	for (auto& d : d_)
		d *= scale_ * get("maxThickness");
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Naca4DigitModifiedDistribution::buildInputMap() noexcept
{
	store("maxThickness",			NAN);	// [-] - % of chord
	store("maxThicknessPosition",	0.3);	// [-] - % of chord
	store("radiusIndex",			6.0);	// [-]
}


void Naca4DigitModifiedDistribution::check() const
{
	checkMaxThickness();
	checkMaxThicknessPosition();
	checkRadiusIndex();
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca4DigitModifiedDistribution::Naca4DigitModifiedDistribution
(
	const Stringmap<>& input
)
:
	a_
	{
		0,		// dummy
	   -0.1260,
	   -0.3516,
		0.2834
	},
	d_
	{
		0.0020,
		0,		// dummy
		0,		// dummy
		0		// dummy
	}
{
	buildInputMap();
	addOptional
	(
		"maxThicknessPosition",
		"radiusIndex"
	);
	parse(input);
	check();

	computeA0();
	lookUpD1();
	computeD2();
	computeD3();

	scaleCoefficients();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Naca4DigitModifiedDistribution::getThicknessAt
(
	const double x
) const noexcept
{
	// leading edge to M
	if (x < get("maxThicknessPosition"))
		return a_[0] * std::sqrt(x) +
			   a_[1] * x +
			   a_[2] * std::pow(x, 2) +
			   a_[3] * std::pow(x, 3);
	// M to trailing edge
	else
		return d_[0] +
			   d_[1] * (chord_ - x) +
			   d_[2] * std::pow((chord_ - x), 2) +
			   d_[3] * std::pow((chord_ - x), 3);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
