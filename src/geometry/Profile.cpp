/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <utility>
#include <vector>

#include "Profile.h"
#include "Axis.h"
#include "Error.h"
#include "Line.h"
#include "Point.h"
#include "ProfileGenerator.h"
#include "Spline.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Profile::rotate(const double angle)
{
	if (wrapped_)
		THROW_RUNTIME_ERROR("profile is wrapped");
		
	double rad {degToRad(angle)};
	double x;
	double y;

	for (auto& p : points_)
	{
		x = p[Axis::X];
		y = p[Axis::Y];

		p[Axis::X] = x * std::cos(rad) - y * std::sin(rad);
		p[Axis::Y] = x * std::sin(rad) + y * std::cos(rad);
	}
}


void Profile::scale(const double factor)
{
	if (wrapped_)
		THROW_RUNTIME_ERROR("profile is wrapped");

	for (auto& p : points_)
	{
		p[Axis::X] *= factor;
		p[Axis::Y] *= factor;
		p[Axis::Z] *= factor;
	}
}


void Profile::translate(const PointCoordinates& coordinates) noexcept
{
	PointCoordinates center {getCenter()};

	PointCoordinates vector
	{
		coordinates[Axis::X] - center[Axis::X],
		coordinates[Axis::Y] - center[Axis::Y],
		coordinates[Axis::Z] - center[Axis::Z]
	};

	for (auto& p : points_)
	{
		p[Axis::X] += vector[Axis::X];
		p[Axis::Y] += vector[Axis::Y];
		p[Axis::Z] += vector[Axis::Z];
	}

}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Profile::Iterator Profile::begin()
{
	return points_.begin();
}


Profile::Constiterator Profile::begin() const
{
	return points_.begin();
}


void Profile::build
(
	const ProfileGenerator& generator,
	const double chord,
	const double radius,
	const double stagger
)
{
	points_.clear();

	for (const auto& p : generator)
		points_.push_back(p);

	// center on origin
	translate(origin_);

	scale(chord);
	translate
	(
		PointCoordinates {0.0, 0.0, radius}
	);
	rotate(stagger);
}


bool Profile::empty() const noexcept
{
	return points_.empty();
}


Profile::Iterator Profile::end()
{
	return points_.end();
}


Profile::Constiterator Profile::end() const
{
	return points_.end();
}


PointCoordinates Profile::getCenter() const noexcept
{
	if (points_.empty())
		return origin_;

	PointCoordinates center {origin_};

	for (const auto& p : points_)
	{
		center[Axis::X] += p[Axis::X];
		center[Axis::Y] += p[Axis::Y];
		center[Axis::Z] += p[Axis::Z];
	}

	for (auto& p : center)
		p /= static_cast<double>(size());

	return std::move(center);
}


Spline Profile::getContour() const
{
	if (empty())
		THROW_RUNTIME_ERROR("profile not built");
	
	return std::move
	(
		Spline {getPoints()}
	);
}


std::vector<Point> Profile::getPoints() const noexcept
{
	std::vector<Point> points;

	for (const auto& p : points_)
		points.push_back(p);

	return std::move(points);
}


Line Profile::getTrailingEdge() const
{
	if (empty())
		THROW_RUNTIME_ERROR("profile not built");

	Point lower
	{
		points_.back()
	};
	Point upper
	{
		points_.front()
	};

	return std::move
	(
		Line {lower, upper}
	);
}


bool Profile::isWrapped() const noexcept
{
	return wrapped_;
}


Profile::Pcvector::size_type Profile::size() const noexcept
{
	return points_.size();
}


void Profile::wrap() noexcept
{
	if (points_.empty())
		return;

	double radius;	// [m]
	double angle;	// [rad]

	PointCoordinates wp;

	// compute wrapped coordinates
	for (auto& p : points_)
	{
		radius = p[Axis::Z];
		angle = p[Axis::Y] / radius;

		wp[Axis::X] = p[Axis::X];
		wp[Axis::Y] = radius * std::sin(angle);
		wp[Axis::Z] = radius * std::cos(angle);

		std::swap(p, wp);
	}

	wrapped_ = true;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
