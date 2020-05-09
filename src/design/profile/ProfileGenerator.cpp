/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>

#include "ProfileGenerator.h"

#include "CircularArcCamber.h"
#include "ConstantDistribution.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Naca2DigitCamber.h"
#include "Naca4DigitDistribution.h"
#include "NoCamber.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void ProfileGenerator::createCamberGenerator(const input::Registry& reg)
{
	if
	(
		!input::InputRegistry::has("Camber")
	)
		cGen_.reset
		(
			new CircularArcCamber {reg}
		);
	else
	{
		auto type
		{
			input::InputRegistry::get("Camber")
		};

		if (type == Naca2DigitCamber::name)
			cGen_.reset
			(
				new Naca2DigitCamber {reg}
			);
		else if (type == CircularArcCamber::name)
			cGen_.reset
			(
				new CircularArcCamber {reg}
			);
		else if (type == NoCamber::name)
			cGen_.reset
			(
				new NoCamber {reg}
			);
		else
			error(FUNC_INFO, "unknown Camber: ", type);
	}
}


void ProfileGenerator::createDistributionGenerator()
{
	if
	(
		!input::InputRegistry::has("Distribution")
	)
		dGen_.reset
		(
			new Naca4DigitDistribution {}
		);
	else
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
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileGenerator::ProfileGenerator(const input::Registry& reg)
{
	reset(reg);
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


void ProfileGenerator::reset(const input::Registry& reg)
{
	createCamberGenerator(reg);
	createDistributionGenerator();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
