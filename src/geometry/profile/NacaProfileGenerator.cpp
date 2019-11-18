/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "NacaProfileGenerator.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const std::map<int, double> NacaProfileGenerator::d1Table_
{
	{2, 0.200},
	{3, 0.234},
	{4, 0.315},
	{5, 0.465},
	{6, 0.700}
};


const double NacaProfileGenerator::scale_ {5.0};


const double NacaProfileGenerator::chord_ {1.0};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void NacaProfileGenerator::parseSeries(const std::string& series)
{
	auto toDouble = [series](int count, int pos)
	{
		return std::stod(series.substr(count, pos));
	};

	auto pos {series.find('-')};

	// if 4-digit modified series
	if (series.size() == 7 && pos == 4)
	{
		I_ = toDouble(5, 1);
		M_ = toDouble(6, 1) * 0.1;

		if (!isInRange(M_, 0.2, 0.6))
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseSeries(const std::string&): "
				"Invalid value of keyword \"series\", "
				"position of max thickness out of range [2,6]"
			);
	}
	// if not 4-digit series
	else if
	(
		series.size() != 4 &&
		pos != std::string::npos
	)
		throw std::invalid_argument
		(
			"turbo::geometry::NacaProfileGenerator::"
			"parseSeries(const std::string&): "
			"Invalid value of keyword \"series\""
		);

	// see the Description section of
	// the header file for an explanation
	m_ = toDouble(0, 1) * 0.01;
	p_ = toDouble(1, 1) * 0.1;
	t_ = toDouble(2, 2) * 0.01;

	if
	(
		isEqual(m_, 0.0) ||
		isEqual(p_, 0.0)
	)
		if
		(
			!isEqual(m_, 0.0) ||
			!isEqual(p_, 0.0)
		)
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseSeries(const std::string&): "
				"Invalid value of keyword \"series\""
			);
}


void NacaProfileGenerator::setSpacingIncrement
(
	const int numberOfPoints = 40
) noexcept
{
	if (spacingType_ == spacing_::LINEAR)
		spacingIncrement_ = chord_ / static_cast<double>(numberOfPoints - 1);
	// spacing_::COSINE is default
	else
		spacingIncrement_ = pi / static_cast<double>(numberOfPoints - 1);
}


void NacaProfileGenerator::computeA0() noexcept
{
	a_[0] = 0.2969 * I_ / 6.0;
}


void NacaProfileGenerator::lookUpD1() noexcept
{
	int m
	{
		static_cast<int>(std::round(10.0 * M_))
	};

	d_[1] = d1Table_.find(m)->second;
}


void NacaProfileGenerator::computeD2() noexcept
{
	double B {chord_ - M_};

	d_[2] = (-3.0*d_[0] - 2.0*d_[1]*B + 0.3) / std::pow(B, 2);
}


void NacaProfileGenerator::computeD3() noexcept
{
	double B {chord_ - M_};

	d_[3] = (-d_[1]/std::pow(B, 2) - 2.0*d_[2]/B) / 3.0;
}


void NacaProfileGenerator::scaleCoefficients() noexcept
{
	for (int i {0}; i < 4; i++)
	{
		a_[i] *= scale_*t_;
		d_[i] *= scale_*t_;
	}
}


void NacaProfileGenerator::generateCamberLine() noexcept
{
	double x {0.0};
	double y {0.0};

	while (isLessOrEqual(x, chord_))
	{
		camberLine_.push_back
		(
			std::make_pair(x, y)
		);

		x = computeCamberX(x);
		y = computeCamberY(x);

		// don't go in circles
		if (camberLine_.back().first > x)
			break;
	}
}


double NacaProfileGenerator::computeCamberX(const double x) const noexcept
{
	if (spacingType_ == spacing_::LINEAR)
	{
		return x + spacingIncrement_;
	}
	// spacing_::COSINE is default
	else
	{
		double angle
		{
			pi + static_cast<double>(camberLine_.size()) * spacingIncrement_
		};

		// scale and shift the unit circle
		return 0.5 * chord_ * (1.0 + std::cos(angle));
	}
}


double NacaProfileGenerator::computeCamberY(const double x) const noexcept
{
	if
	(
		isEqual(p_, 0.0) ||
		isEqual(m_, 0.0)
	)
		return 0.0;
	else if (x < M_)
		return m_ / std::pow(p_, 2) *
			(
				2.0 * p_ * x - std::pow(x, 2)
			);
	else
		return m_ / std::pow((1.0 - p_), 2) *
			(
				1.0 - 2.0 * p_ + 2.0 * p_ * x - std::pow(x, 2)
			);
}


double NacaProfileGenerator::computeThickness(const double x) const noexcept
{
	// leading edge to M
	if (x < M_)
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


double NacaProfileGenerator::computeInclination(const double x) const noexcept
{
	double dydx;

	if
	(
		isEqual(p_, 0.0) ||
		isEqual(m_, 0.0)
	)
		dydx = 0.0;
	else if (x < M_)
		dydx = 2.0 * m_ / std::pow(p_, 2) * (p_ - x);
	else
		dydx = 2.0 * m_ / std::pow((1.0 - p_), 2) * (p_ - x);
	
	return std::atan(dydx);
}


double NacaProfileGenerator::computeDX
(
	const double thickness,
	const double inclination
) const noexcept
{
	return - thickness * std::sin(inclination);
}


double NacaProfileGenerator::computeDY
(
	const double thickness,
	const double inclination
) const noexcept
{
	return thickness * std::cos(inclination);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void NacaProfileGenerator::parseInput(const Stringmap& input)
{
	auto series {input.find("series")};
	auto numberOfPoints {input.find("numberOfPoints")};
	auto spacingType {input.find("spacingType")};

	if (series == input.end())
		throw std::runtime_error
		(
			"turbo::geometry::NacaProfileGenerator::"
			"parseInput(const turbo::Stringmap&): "
			"Keyword \"series\" undefined"
		);

	parseSeries(series->second);

	if (spacingType != input.end())
	{
		if (spacingType->second == "linear")
			spacingType_ = spacing_::LINEAR;
		else if (spacingType->second == "cosine")
			spacingType_ = spacing_::COSINE;
		else
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseInput(const turbo::Stringmap&): "
				"Invalid value for keyword \"spacingType\""
			);
	}
	
	if (numberOfPoints != input.end())
	{
		int number {std::stoi(numberOfPoints->second)};
		if (number <= 0)
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseInput(const turbo::Stringmap&): "
				"Invalid value for keyword \"numberOfPoints\""
			);

		setSpacingIncrement(number);
	}
	else
		setSpacingIncrement();
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

NacaProfileGenerator::NacaProfileGenerator(const Stringmap& input)
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
	},
	I_ {6.0},
	M_ {0.3},
	spacingType_ {spacing_::COSINE}
{
	parseInput(input);

	computeA0();
	lookUpD1();
	computeD2();
	computeD3();

	scaleCoefficients();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void NacaProfileGenerator::generate() noexcept
{
	if (!isEmpty())
		return;

	double thickness;
	double inclination;
	double dx;
	double dy;

	generateCamberLine();

	for (auto p : camberLine_)
	{
		thickness = computeThickness(p.first);
		inclination = computeInclination(p.first);

		dx = computeDX(thickness, inclination);
		dy = computeDY(thickness, inclination);

		xyUpper_.push_back
		(
			std::make_pair
			(
				p.first + dx,
				p.second + dy
			)
		);
		xyLower_.push_back
		(
			std::make_pair
			(
				p.first - dx,
				p.second - dy
			)
		);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
