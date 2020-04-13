/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "Profile.h"

#include "Error.h"
#include "General.h"
#include "Geometry.h"
#include "ProfileGenerator.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Profile::centerOn(const Point& p) noexcept
{
	translate
	(
		Vector {p - centroid()}
	);
}


void Profile::rotate2D(const Float angle) noexcept
{
	Float x_top;
	Float y_top;
	Float x_bot;
	Float y_bot;

	for (auto& [top, bot] : points_)
	{
		x_top = top.x();
		y_top = top.y();
		x_bot = bot.x();
		y_bot = bot.y();

		top.x() = x_top * std::cos(angle) - y_top * std::sin(angle);
		top.y() = x_top * std::sin(angle) + y_top * std::cos(angle);
		bot.x() = x_bot * std::cos(angle) - y_bot * std::sin(angle);
		bot.y() = x_bot * std::sin(angle) + y_bot * std::cos(angle);
	}
}


void Profile::scale(const Float factor) noexcept
{
	scale(centroid(), factor);
}


void Profile::scale(const Point& p, const Float factor) noexcept
{
	for (auto& [top, bot] : points_)
	{
		top = p + (top - p) * factor;
		bot = p + (bot - p) * factor;
	}
}


void Profile::translate(const Vector& v) noexcept
{
	for (auto& [top, bot] : points_)
	{
		top += v;
		bot += v;
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
	const input::Chord& chord,
	const input::Radius& radius,
	const input::StaggerAngle& stagger
)
{
	wrapped_ = false;

	points_ = generator.generate();

	scale(chord.value());
	centerOn
	(
		Point {0.0, 0.0, radius.value()}
	);
	rotate2D(stagger.value());
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


Profile::Point Profile::centroid() const noexcept
{
	Point center {Point::origin()};

	for (const auto& [top, bot] : points_)
		center += top + bot;

	center /= static_cast<Float>(2 * size());

	return center;
}


Vector Profile::leDirection() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	auto [top, bot]				// next to LE contour points
	{
		*(points_.begin() + 1)
	};

	// because it should point outward
	return unit
	(
		lePoint() - midpoint(top, bot)
	);
}


Profile::Point Profile::lePoint() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	auto [top, bot]
	{
		*points_.begin()
	};

	return midpoint(top, bot);
}


geometry::Spline Profile::getContour() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	return geometry::Spline {getPoints()};
}


std::vector<geometry::Point> Profile::getPoints() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	// we have to map from a pair list --- top - bot
	// ordered from LE to TE, to a uniquely single-valued list
	// ordered from top-TE to bot-TE i.e. we have to
	// skip one LE point (both top and bot lists have it)
	// and unwrap (reorder) the list properly, eg:
	// [[0, 0], [1, 1], [2, 2]] -> [2, 1, 0, 1, 2]
	std::vector<geometry::Point> points;
	points.reserve(2 * size() - 1);

	for (auto i {size() - 1}; i > 0; --i)
		points.push_back(points_[i].first);

	for (auto& p : points_)
		points.push_back(p.second);

	return points;
}


geometry::Line Profile::getTrailingEdge() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	// from bot-TE to top-TE
	return geometry::Line
	{
		geometry::Point {points_.back().first},
		geometry::Point {points_.back().second}
	};
}


Vectorpair<Profile::Point> Profile::points() const noexcept
{
	return points_;
}


Profile::Sizetype Profile::size() const noexcept
{
	return points_.size();
}


Vector Profile::teDirection() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	auto [top, bot]				// next to TE contour points
	{
		*(points_.rbegin() + 1)
	};

	// because it should point outward
	return unit
	(
		tePoint() - midpoint(top, bot)
	);
}


Profile::Point Profile::tePoint() const
{
	if (empty())
		THROW_LOGIC_ERROR("profile not build");

	auto [top, bot]
	{
		*points_.rbegin()
	};

	return midpoint(top, bot);
}


void Profile::wrap() noexcept
{
	if (wrapped_)
		return;

	Float r;		// radius
	Float a_top;	// angle
	Float a_bot;

	// compute wrapped coordinates
	for (auto& [top, bot] : points_)
	{
		r = top.z();		// z_top == z_bot
		a_top = top.y() / r;
		a_bot = bot.y() / r;

		top.y() = r * std::sin(a_top);
		top.z() = r * std::cos(a_top);
		bot.y() = r * std::sin(a_bot);
		bot.z() = r * std::cos(a_bot);
	}

	wrapped_ = true;
}


bool Profile::wrapped() const noexcept
{
	return wrapped_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
