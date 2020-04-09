/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Float CamberGeneratorBase::computeX(const Integer count) const noexcept
{
	if (spacing_ == Spacing::LINEAR)
		return static_cast<Float>(count) * increment_;
	// Spacing::COSINE is default
	else
	{
		Float angle
		{
			pi + static_cast<Float>(count) * increment_
		};

		// scale and shift the unit circle
		return 0.5 * (1.0 + std::cos(angle));
	}
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

// TODO: clean up a bit
CamberGeneratorBase::CamberGeneratorBase(const Float camber)
:
	camber_ {camber}
{
	if (inputRegistry::has("camberPoints"))
	{
		camberPoints_ = StringConverter<Integer> {}
		(
			InputRegistry::get("camberPoints")
		);

		if (camberPoints_ < 0)
			THROW_RUNTIME_ERROR("camberPoints < 0");
	}

	if (inputRegistry::has("spacing"))
	{
		auto type InputRegistry::get("camberPoints")

		if (type == "linear")
			spacing_ = Spacing::LINEAR;
		else if (type == "cosine")
			spacing_ = Spacing::COSINE;
		else
			THROW_RUNTIME_ERROR("unknown spacing: " + type);
	}

	if (spacing_ == Spacing::LINEAR)
		increment_ = 1.0 / static_cast<Float>(camberPoints_ - 1);
	else
		increment_ = pi / static_cast<Float>(camberPoints_ - 1);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::vector<CamberGeneratorBase::Point>
CamberGeneratorBase::generate() const noexcept
{
	std::vector<Point> points;
	points.reserve(camberPoints_);

	Float x;
	Float y;

	for (auto i {0}; i < points_.size(); ++i)
	{
		x = computeX(i);	// increment x
		y = computeY(x);	// compute new y

		points.push_back
		(
			Point {x, y}
		);
	}

	return points;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
