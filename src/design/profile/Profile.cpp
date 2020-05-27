/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <cassert>
#include <vector>

#include "Profile.h"

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "Line.h"
#include "Point.h"
#include "ProfileGenerator.h"
#include "Registry.h"
#include "Spline.h"
#include "Utility.h"
#include "Variables.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Profile::Reference Profile::back()
{
	return points_.back();
}


Profile::Constreference Profile::back() const
{
	return points_.back();
}


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
	const input::Registry& reg
)
{
	radius_ = reg.cref<input::Radius>().value();
	auto chord
	{
		reg.cref<input::Chord>()
	};
	auto stagger
	{
		reg.cref<input::StaggerAngle>()
	};

	wrapped_ = false;

	points_ = generator.generate();

	scale(chord.value());
	centerOn
	(
		Point {0.0, 0.0, radius_}
	);
	rotateZ(stagger.value());
}


std::vector<Profile::Point> Profile::camberLine() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	std::vector<Profile::Point> camberLine;
	camberLine.reserve(points_.size());

	for (auto& [top, bot] : points_)
		camberLine.emplace_back
		(
			midpoint(top, bot)
		);

	return camberLine;
}


Profile::Point Profile::centroid() const noexcept
{
	Point center {Point::origin()};

	for (const auto& [top, bot] : points_)
		center += top + bot;

	center /= static_cast<Float>(2 * size());

	return center;
}


void Profile::centerOn(const Point& p) noexcept
{
	translate
	(
		Vector {p - centroid()}
	);
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


Profile::Reference Profile::front()
{
	return points_.front();
}


Profile::Constreference Profile::front() const
{
	return points_.front();
}


geometry::Spline Profile::getContour() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return geometry::Spline {orderedPoints()};
}


Sptrvector<geometry::Curve> Profile::getFullContour() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Sptrvector<geometry::Curve> curves;

	std::vector<Point> tmpTop;
	std::vector<Point> tmpBot;
	tmpTop.reserve(points_.size());
	tmpBot.reserve(points_.size());

	for (auto& [top, bot] : points_)
	{
		tmpTop.emplace_back(top);
		tmpBot.emplace_back(bot);
	}
	std::reverse(tmpTop.begin(), tmpTop.end());

	curves.emplace_back
	(
		new geometry::Spline {tmpTop}
	);
	curves.emplace_back
	(
		new geometry::Spline
		{
			curves.front()->endPtr(),
			tmpBot
		}
	);
	curves.emplace_back
	(
		new geometry::Line
		{
			curves.back()->endPtr(),
			curves.front()->startPtr()
		}
	);

	return curves;
}


std::vector<geometry::Point> Profile::getPoints() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	std::vector<Profile::Point> op {orderedPoints()};

	std::vector<geometry::Point> points;
	points.reserve(op.size());

	for (auto& p : op)
		points.push_back(p);

	return points;
}


geometry::Line Profile::getTrailingEdge() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	// from bot-TE to top-TE
	return geometry::Line
	{
		points_.back().first,
		points_.back().second
	};
}


Vector Profile::leDirection() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

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


Profile::Point Profile::lePoint() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	auto [top, bot]
	{
		*points_.begin()
	};

	return midpoint(top, bot);
}


std::vector<Profile::Point> Profile::orderedPoints() const noexcept
{
	// we have to map from a pair list --- top - bot
	// ordered from LE to TE, to a uniquely single-valued list
	// ordered from top-TE to bot-TE i.e. we have to
	// skip one LE point (both top and bot lists have it)
	// and unwrap (reorder) the list properly, eg:
	// [[0, 0], [1, 1], [2, 2]] -> [2, 1, 0, 1, 2]
	std::vector<Point> points;
	points.reserve(2 * size() - 1);

	for (auto i {size() - 1}; i > 0; --i)
		points.push_back(points_[i].first);

	for (auto& p : points_)
		points.push_back(p.second);

	return points;
}


Profile::Data Profile::points() const noexcept
{
	return points_;
}


void Profile::rotateX(const Float angle) noexcept
{
	rotate<0>(angle);
}


void Profile::rotateY(const Float angle) noexcept
{
	rotate<1>(angle);
}


void Profile::rotateZ(const Float angle) noexcept
{
	rotate<2>(angle);
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


Profile::Sizetype Profile::size() const noexcept
{
	return points_.size();
}


Vector Profile::teDirection() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

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


Profile::Point Profile::tePoint() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	auto [top, bot]
	{
		*points_.rbegin()
	};

	return midpoint(top, bot);
}


void Profile::translate(const Vector& v) noexcept
{
	for (auto& [top, bot] : points_)
	{
		top += v;
		bot += v;
	}
}


void Profile::wrap() noexcept
{
	if (wrapped_)
		return;

	for (auto& [top, bot] : points_)
	{
		Float aTop {top.y() / radius_};
		Float aBot {bot.y() / radius_};

		top.y() = radius_ * std::sin(aTop);
		top.z() = radius_ * std::cos(aTop);
		bot.y() = radius_ * std::sin(aBot);
		bot.z() = radius_ * std::cos(aBot);
	}

	wrapped_ = true;
}


bool Profile::wrapped() const noexcept
{
	return wrapped_;
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Profile::Reference Profile::operator[](Sizetype pos)
{
	return points_[pos];
}


Profile::Constreference Profile::operator[](Sizetype pos) const
{
	return points_[pos];
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
