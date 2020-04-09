/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>
#include <memory>

#include "ConstantDistribution.h"
#include "CircularArcCamber.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Naca2DigitCamber.h"
#include "Naca4DigitDistribution.h"
#include "ProfileGenerator.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void ProfileGenerator::createCamberGenerator(const Float camber)
{
	Word type
	{
		InputRegistry::get("camber")
	};

	if (type == "naca2Digit")
		cGen_.reset
		(
			std::make_unique<Naca2DigitCamber>(camber)
		);
	else if (type == "circularArc")
		cGen_.reset
		(
			std::make_unique<CircularArcCamber>(camber)
		);
	else
		THROW_RUNTIME_ERROR("unknown camber: " + type);
}


void ProfileGenerator::createDistributionGenerator()
{
	Word type
	{
		InputRegistry::get("distribution")
	};

	if (type == "constant")
		dGen_.reset
		(
			std::make_unique<ConstantDistribution>()
		);
	else if (type == "naca4Digit")
		dGen_.reset
		(
			std::make_unique<Naca4DigitDistribution>()
		);
	else
		THROW_RUNTIME_ERROR("unknown distribution: " + type);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileGenerator::ProfileGenerator(const Float camber)
{
	reset(camber);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Vectorpair<ProfileGenerator::Point> ProfileGenerator::generate() const
{
	auto camberLine {cGen_->generate()};

	// apply distribution to camber line
	Vectorpair<Point> points;
	points.reserve(camberLine.size());

	Float x;
	Float y;
	Float thickness;		// half of total thickness
	Float inclination;
	Float dx;
	Float dy;

	for (const auto& p : camberLine)
	{
		x = p.x();
		y = p.y();

		thickness = dGen_->thickness(x);
		inclination = cGen_->inclination(x);

		dx = thickness * std::sin(inclination);
		dy = thickness * std::cos(inclination);

		points.push_back
		(
			std::make_pair
			(
				Point	// upper surface
				{
					x - dx,
					y + dy
				},
				Point	// lower surface
				{
					x + dx,
					y - dy
				}
			)
		);
	}

	return points;
}


Float ProfileGenerator::inclination(const Float x) const noexcept
{
	return cGen_->inclination(x);
}


void ProfileGenerator::reset(const Float camber) const
{
	createCamberGenerator(camber);
	createDistributionGenerator();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
