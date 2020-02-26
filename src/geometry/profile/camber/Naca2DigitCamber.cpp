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
#include "Naca2DigitCamber.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

double Naca2DigitCamber::computeMaxCamber
(
	const double camberAngle,
	const double maxCamberPosition
) const noexcept
{
	double theta {degToRad(camberAngle)};
	double root
	{
		0.25 / std::pow(std::tan(theta), 2) +
		maxCamberPosition * (1.0 - maxCamberPosition)
	};
	double max
	{
		-0.25 / std::tan(theta) + 0.5 * std::sqrt(root)
	};

	return max;
}


double Naca2DigitCamber::computeMaxCamberPosition
(
	const double camberAngle,
	const double maxCamber
) const noexcept
{
	double theta {degToRad(camberAngle)};
	double root
	{
		1.0 - 8.0 * maxCamber * (2.0 * maxCamber + 1.0 / std::tan(theta))
	};
	double pos
	{
		0.5 + 0.5 * std::sqrt(root)
	};

	return pos;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Naca2DigitCamber::buildInputMap() noexcept
{
	store("maxCamberPosition", 0.5);	// [-] - % of chord
}


void Naca2DigitCamber::check() const
{
	if
	(
		!isInRange(get("maxCamberPosition"), 0.0, 0.9)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxCamberPosition' out of range [0, 0.9]");

	if
	(
		hasValue("maxCamber") &&
		!isInRange(get("maxCamber"), 0.0, 0.09)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxCamber' out of range [0, 0.09]");
}


void Naca2DigitCamber::computeParameters(const double camberAngle)
{
	double pos {get("maxCamberPosition")};
	double max
	{
		computeMaxCamber(camberAngle, pos)
	};

/*	we do not respect the conventional limit
	if (max > 0.09)
	{
		max = 0.09;
		pos = computeMaxCamberPosition(camberAngle, max);
	}
*/

	store("maxCamber", max);
	store("maxCamberPosition", pos);

	check();
}


double Naca2DigitCamber::computeY(const double x) const
{
	double max {get("maxCamber")};
	double pos {get("maxCamberPosition")};

	if (x < pos)
		return max / std::pow(pos, 2) *
			(
				2.0 * pos * x - std::pow(x, 2)
			);
	else
		return max / std::pow((1.0 - pos), 2) *
			(
				1.0 - 2.0 * pos + 2.0 * pos * x - std::pow(x, 2)
			);
}


void Naca2DigitCamber::parse(const Stringmap<>& input)
{
	InputObjectBase::parse(input);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca2DigitCamber::Naca2DigitCamber(const Stringmap<>& input)
:
	CamberGeneratorBase {input}
{
	buildInputMap();
	addOptional("maxCamberPosition");
	parse(input);
	check();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double Naca2DigitCamber::getInclinationAt(const double x) const
{
	if
	(
		!isInRange(x, 0.0, chord_)
	)
		THROW_DOMAIN_ERROR("x out of range [0, chord]");

	double max {get("maxCamber")};
	double pos {get("maxCamberPosition")};
	double dydx;

	if (x < pos)
		dydx = 2.0 * max / std::pow(pos, 2) * (pos - x);
	else
		dydx = 2.0 * max / std::pow((1.0 - pos), 2) * (pos - x);

	return radToDeg(std::atan(dydx));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
