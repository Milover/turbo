/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>

#include "Axis.h"
#include "CamberGeneratorBase.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

double CamberGeneratorBase::computeX(const double x) const noexcept
{
	if (spacing_ == SpacingType::LINEAR)
	{
		return x + increment_;
	}
	// spacing_::COSINE is default
	else
	{
		// using size because camber line is growing (push_back())
		double angle
		{
			pi + static_cast<double>(camber_.size()) * increment_
		};

		// scale and shift the unit circle
		return 0.5 * chord_ * (1.0 + std::cos(angle));
	}
}


void CamberGeneratorBase::parseCamberPoints(const std::string& value)
{
	try
	{
		camberPoints_ = std::stoi(value);
	}
	catch (...)
	{
		THROW_ARGUMENT_ERROR("can't convert '" + value + "' to int");
	}
}


void CamberGeneratorBase::parseSpacing(const std::string& value)
{
	if (value == "linear")
		spacing_ = SpacingType::LINEAR;
	else if (value == "cosine")
		spacing_ = SpacingType::COSINE;
	else
		THROW_RUNTIME_ERROR("unknown value '" + value + "' for keyword 'spacing'");
}


void CamberGeneratorBase::setIncrement() noexcept
{
	if (spacing_ == SpacingType::LINEAR)
		increment_ = chord_ / static_cast<double>(camberPoints_ - 1);
	// SpacingType::COSINE is default
	else
		increment_ = pi / static_cast<double>(camberPoints_ - 1);
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

CamberGeneratorBase::CamberGeneratorBase(const Stringmap<>& input)
{
	parse(input);
	check();

	setIncrement();
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void CamberGeneratorBase::check() const
{
	if (camberPoints_ <= 0)
		THROW_RUNTIME_ERROR("value of keyword 'camberPoints' <= 0");
}


double CamberGeneratorBase::convert(const std::string& value) const
{
	try
	{
		return std::stod(value);
	}
	catch (...)
	{
		THROW_ARGUMENT_ERROR("can't convert '" + value + "' to double");
	}
}


void CamberGeneratorBase::parse(const Stringmap<>& input)
{
	auto points {input.find("camberPoints")};
	auto spacing {input.find("spacing")};

	std::string value;

	if (points != input.end())
	{
		value = points->second;
		parseCamberPoints(value);
	}

	if (spacing != input.end())
	{
		value = spacing->second;
		parseSpacing(value);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

CamberGeneratorBase::Iterator CamberGeneratorBase::begin()
{
	return camber_.begin();
}


CamberGeneratorBase::Constiterator CamberGeneratorBase::begin() const
{
	return camber_.begin();
}


bool CamberGeneratorBase::empty() const noexcept
{
	return camber_.empty();
}


CamberGeneratorBase::Iterator CamberGeneratorBase::end()
{
	return camber_.end();
}


CamberGeneratorBase::Constiterator CamberGeneratorBase::end() const
{
	return camber_.end();
}


void CamberGeneratorBase::generate(const double camberAngle) noexcept
{
	if
	(
		camberAngle < 0.0 &&
		camberAngle > 90.0
	)
		THROW_DOMAIN_ERROR("camber angle out of range [0, 90]");

	camber_.clear();

	computeParameters(camberAngle);

	PointCoordinates p {0.0, 0.0, 0.0};
	while
	(
		isLessOrEqual(p[Axis::X], chord_)
	)
	{
		camber_.push_back(p);

		p[Axis::X] = computeX(p[Axis::X]);
		p[Axis::Y] = computeY(p[Axis::X]);

		// don't go in circles
		if
		(
			camber_.back()[Axis::X] > p[Axis::X]
		)
			break;
	}
}


bool CamberGeneratorBase::hasValue(const std::string& key) const noexcept
{
	return hasKey(key);
}


int CamberGeneratorBase::size() const noexcept
{
	return camber_.size();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
