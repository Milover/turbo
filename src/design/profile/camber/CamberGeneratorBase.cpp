/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "CamberGeneratorBase.h"

#include "Error.h"
#include "General.h"
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Float CamberGeneratorBase::computeX(const Integer count) const noexcept
{
	if (spacing_.value() == Spacing::LINEAR)
		return static_cast<Float>(count) * increment_;
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

CamberGeneratorBase::CamberGeneratorBase(const input::CamberAngle& camber)
:
	nPoints_
	{
		input::read<input::NumberOfCamberPoints>()
	},
	spacing_
	{
		input::read<input::CamberPointSpacing>()
	},
	camber_ {camber}
{
	if (spacing_.value() == Spacing::LINEAR)
		increment_ = 1.0 / static_cast<Float>(nPoints_.value() - 1);
	else
		increment_ = pi / static_cast<Float>(nPoints_.value() - 1);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

std::vector<CamberGeneratorBase::Point>
CamberGeneratorBase::generate() const noexcept
{
	std::vector<Point> points;
	points.reserve(nPoints_.value());

	Float x;
	Float y;

	for (auto i {0}; i < nPoints_.value(); ++i)
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
