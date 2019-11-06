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


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void NacaProfileGenerator::parseSeries(const std::string& series)
{
	auto toDouble = [series](int count, int pos)
	{
		return std::stod(series.substr(count, pos));
	};

	auto pos {series.find('-')};
	
	// 4-digit series
	if (series.size() == 4 && pos != std::string::npos)
	{
		I_ = 6.0;
		M_ = 0.3;
	}
	// 4-digit modified series
	else if (series.size() == 7 && pos == 4)
	{
		I_ = toDouble(5, 1);
		M_ = toDouble(6, 1) * 0.1;

		if (M_ < 0.2 || M_ > 0.6)
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseSeries(const std::string&): "
				"Invalid value of keyword \"series\", "
				"position of max thickness out of range [2,6]"
			);
	}
	else
		throw std::invalid_argument
		(
			"turbo::geometry::NacaProfileGenerator::"
			"parseSeries(const std::string&): "
			"Invalid value of keyword \"series\""
		);
	
	m_ = toDouble(0, 1) * 0.01;
	p_ = toDouble(1, 1) * 0.1;
	t_ = toDouble(2, 2) * 0.01;
}


void NacaProfileGenerator::computeA0()
{
	a_[0] = 0.2969 * I_ / 6.0;
}


void NacaProfileGenerator::lookUpD1()
{
	int m
	{
		static_cast<int>(std::round(10.0 * M_))
	};

	d_[1] = d1Table_.find(m)->second;
}


void NacaProfileGenerator::computeD2()
{
	double B {1.0 - M_};

	d_[2] = (-3.0*d_[0] - 2.0*d_[1]*B + 1.5*t_) / std::pow(B, 2);
}


void NacaProfileGenerator::computeD3()
{
	double B {1.0 - M_};

	d_[3] = (-d_[1]/std::pow(B, 2) - 2.0*d_[2]/B) / 3.0;
}


void NacaProfileGenerator::scaleCoefficients()
{
	for (int i {0}; i < 4; i++)
	{
		a_[i] *= scale_*t_;
		d_[i] *= scale_*t_;
	}
}


void NacaProfileGenerator::generateCamberLine()
{
	double x {0.0};
	double y {0.0};

	while (!isEqual(x, 1.0))
	{
		camberLine_.push_back
		(
			std::make_pair(x, y)
		);

		x = computeCamberX(x);
		y = computeCamberY(x);

		// if we made a big error
		if (x > 1.0)
			break;
	}
}


double NacaProfileGenerator::computeCamberX(const double x)
{
	double increment;
	
	// see the Description section in
	// the header file for an explanation
	if (x < 0.0125)
		increment = deltaX_ / 40.0;
	else if (x < 0.1)
		increment = deltaX_ / 4.0;
	else
		increment = deltaX_;

	return x + increment;
}


// temporary implementation
double NacaProfileGenerator::computeCamberY(const double x)
{
	return 0.0;
}


double NacaProfileGenerator::computeThickness(const double x) const
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
			   d_[1] * (1.0 - x) +
			   d_[2] * std::pow((1.0 - x), 2) +
			   d_[3] * std::pow((1.0 - x), 3);
}


// temporary implementation
double NacaProfileGenerator::computeInclination(const double x) const
{
	return 0.0;
}


// temporary implementation
double NacaProfileGenerator::computeDX
(
	const double thickness,
	const double inclination
) const
{
	return 0.0;
}


// temporary implementation
double NacaProfileGenerator::computeDY
(
	const double thickness,
	const double inclination
) const
{
	return 0.0;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void NacaProfileGenerator::parseInput(const Stringmap& input)
{
	auto series {input.find("series")};
	auto deltaX {input.find("deltaX")};

	if (series == input.end())
		throw std::runtime_error
		(
			"turbo::geometry::NacaProfileGenerator::"
			"parseInput(const turbo::Stringmap&): "
			"Keyword \"series\" undefined"
		);

	parseSeries(series->second);
	
	if (deltaX != input.end())
	{
		deltaX_ = std::stod(deltaX->second);

		if (deltaX_ < 0.0 || deltaX_ > 1.0)
			throw std::invalid_argument
			(
				"turbo::geometry::NacaProfileGenerator::"
				"parseInput(const turbo::Stringmap&): "
				"Value of keyword \"deltaX\" out of range [0,1]"
			);
	}
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
	deltaX_ {0.01}
{
	parseInput(input);

	computeA0();
	lookUpD1();
	computeD2();
	computeD3();

	scaleCoefficients();
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

NacaProfileGenerator::~NacaProfileGenerator()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void NacaProfileGenerator::generate()
{
	if (!empty())
		return;

	double thickness;
	double inclination;
	double dx;
	double dy;

	generateCamberLine();

	for (auto p : camberLine_)
	{
		thickness = computeThickness(p.first);
		inclination = computeThickness(p.first);

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
