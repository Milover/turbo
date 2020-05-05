/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>
#include <memory>

#include "ProfileGenerator.h"

#include "CamberGenerators.h"
#include "DistributionGenerators.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void ProfileGenerator::createCamberGenerator
(
	const input::CamberAngle& camber
)
{
	auto type
	{
		input::InputRegistry::get("Camber")
	};

	if (type == Naca2DigitCamber::name)
		cGen_.reset
		(
			new Naca2DigitCamber {camber}
		);
	else if (type == CircularArcCamber::name)
		cGen_.reset
		(
			new CircularArcCamber {camber}
		);
	else
		error(FUNC_INFO, "unknown Camber: ", type);
}


void ProfileGenerator::createDistributionGenerator()
{
	auto type
	{
		input::InputRegistry::get("Distribution")
	};

	if (type == ConstantDistribution::name)
		dGen_.reset
		(
			new ConstantDistribution {}
		);
	else if (type == Naca4DigitDistribution::name)
		dGen_.reset
		(
			new Naca4DigitDistribution {}
		);
	else
		error(FUNC_INFO, "unknown Distribution: ", type);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileGenerator::ProfileGenerator(const input::CamberAngle& camber)
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


void ProfileGenerator::reset(const input::CamberAngle& camber)
{
	createCamberGenerator(camber);
	createDistributionGenerator();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
