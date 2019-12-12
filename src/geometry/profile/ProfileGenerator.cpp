/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>
#include <utility>
#include <vector>

#include "Axis.h"
#include "ConstantDistribution.h"
#include "CircularArcCamber.h"
#include "Error.h"
#include "Naca2DigitCamber.h"
#include "Naca4DigitDistribution.h"
#include "Naca4DigitModifiedDistribution.h"
#include "ProfileGenerator.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void ProfileGenerator::initializeCamberGenerator(const Stringmap<>& input)
{
	auto search {input.find("camber")};
	
	if (search == input.end())
		THROW_RUNTIME_ERROR("keyword 'camber' undefined");
	
	std::string type {search->second};

	if (type == "naca2Digit")
		camberGenerator_.reset
		(
			new Naca2DigitCamber {input}
		);
	else if (type == "circularArc")
		camberGenerator_.reset
		(
			new CircularArcCamber {input}
		);
	else
		THROW_RUNTIME_ERROR("unknown value '" + type + "' for keyword 'camber'");
}


void ProfileGenerator::initializeDistributionGenerator(const Stringmap<>& input)
{
	auto search {input.find("distribution")};

	if (search == input.end())
		THROW_RUNTIME_ERROR("keyword 'distribution' undefined");

	std::string type {search->second};

	if (type == "constant")
		distributionGenerator_.reset
		(
			new ConstantDistribution {input}
		);
	else if (type == "naca4Digit")
		distributionGenerator_.reset
		(
			new Naca4DigitDistribution {input}
		);
	else if (type == "naca4DigitModified")
		distributionGenerator_.reset
		(
			new Naca4DigitModifiedDistribution {input}
		);
	else
		THROW_RUNTIME_ERROR("unknown value '" + type + "' for keyword 'distribution'");
}


void ProfileGenerator::finalize
(
	const Vectorpair<PointCoordinates>& profile
) noexcept
{
	// upper surface (we're skipping the LE point)
	int size {static_cast<int>(profile.size())};
	for (int i {size - 1}; i > 0; i--)
		profile_.push_back
		(
			profile[i].first
		);

	// lower surface (we're including the LE point)
	for (const auto& p : profile)
		profile_.push_back
		(
			p.second
		);
}


void ProfileGenerator::generateCamberLine(const double camberAngle) noexcept
{
	camberGenerator_->generate(camberAngle);

	store
	(
		"maxCamber",
		camberGenerator_->get("maxCamber")
	);
	store
	(
		"maxCamberPosition",
		camberGenerator_->get("maxCamberPosition")
	);
	store
	(
		"leadingInclination",
		camberGenerator_->getInclinationAt(0.0)
	);
	store
	(
		"trailingInclination",
		camberGenerator_->getInclinationAt(1.0)
	);
}


void ProfileGenerator::store
(
	const std::string& key,
	const double value
)
{
	data_[key] = value;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ProfileGenerator::ProfileGenerator(const Stringmap<>& input)
:
	data_
	{
		{"leadingInclination",	NAN},	// [deg]
		{"maxCamber",			NAN},	// [-] - % of chord
		{"maxCamberPosition",	NAN},	// [-] - % of chord
		{"trailingInclination",	NAN}	// [deg]
	}
{
	initializeCamberGenerator(input);
	initializeDistributionGenerator(input);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

ProfileGenerator::Iterator ProfileGenerator::begin()
{
	return profile_.begin();
}


ProfileGenerator::Constiterator ProfileGenerator::begin() const
{
	return profile_.begin();
}


bool ProfileGenerator::empty() const noexcept
{
	return profile_.empty();
}


ProfileGenerator::Iterator ProfileGenerator::end()
{
	return profile_.end();
}


ProfileGenerator::Constiterator ProfileGenerator::end() const
{
	return profile_.end();
}


void ProfileGenerator::generate(const double camberAngle)
{
	profile_.clear();

	generateCamberLine(camberAngle);

	// apply distribution to camber line
	Vectorpair<PointCoordinates> profile;
	double x;
	double y;
	double thickness;		// half of total thickness
	double inclination;
	double dx;
	double dy;

	for (const auto& p : *camberGenerator_)
	{
		x = p[Axis::X];
		y = p[Axis::Y];

		thickness = distributionGenerator_->getThicknessAt(x);
		inclination = degToRad(camberGenerator_->getInclinationAt(x));

		dx = -thickness * std::sin(inclination);
		dy = thickness * std::cos(inclination);

		profile.push_back
		(
			std::make_pair
			(
				PointCoordinates	// upper surface
				{
					x + dx,
					y + dy,
					0.0
				},
				PointCoordinates	// lower surface
				{
					x - dx,
					y - dy,
					0.0
				}
			)
		);
	}

	finalize(profile);
}


double ProfileGenerator::get(const std::string& key) const
{
	auto search {data_.find(key)};

	if (search == data_.end())
		THROW_ARGUMENT_ERROR("key '" + key + "' does not exist");

	return search->second;
}


bool ProfileGenerator::hasValue(const std::string& key) const noexcept
{
	auto search {data_.find(key)};

	if (search == data_.end())
		return false;
	else if (std::isnan(search->second))
		return false;
	
	return true;
}


int ProfileGenerator::size() const noexcept
{
	return profile_.size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
