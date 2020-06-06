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

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Profile::constrain(const input::Registry& reg)
{
	if (reg.has<input::MaxPassageWidth>())
		constrainPassageWidth
		(
			reg.cref<input::MaxPassageWidth>().value()
		);

	// constrain local max abs. blade thickness
	if (reg.has<input::MaxAbsBladeThickness>())
		constrainMaxThickness
		(
			reg.cref<input::MaxAbsBladeThickness>().value()
		);
}


void Profile::constrainMaxThickness(const Float maxAbsBladeThickness) noexcept
{
	// we have to find the thickness after wrapping
	Float tMax {0.0};
	Float aMax {0.0};

	// FIXME: this can probably be better
	for (auto& [top, bot] : points_)
	{
		Float tTmp
		{
			std::hypot
			(
				top.x() - bot.x(),
				radius_
			  * (std::sin(top.y() / radius_) - std::sin(bot.y() / radius_))
			)
		};

		if (!isLessOrEqual(tTmp, tMax))
		{
			tMax = tTmp;
			aMax = 0.5 * mag(top - bot);
		}
	}

	if
	(
		isGreaterOrEqual(tMax, maxAbsBladeThickness)
	)
		inflate
		(
			radius_ * std::asin(0.5 * maxAbsBladeThickness / radius_) / aMax
		);
}


void Profile::constrainPassageWidth(const Float maxPassageWidth) noexcept
{
	Float pw {passageWidth()};
	if
	(
		isGreaterOrEqual(pw, maxPassageWidth)
	)
		scale(maxPassageWidth / pw);
}


void Profile::recompute(const input::Registry& reg)
{
	reg.store
	(
		input::Chord {chord()}
	);
	reg.store
	(
		input::Solidity
		{
			reg.cref<input::Chord>(),
			reg.cref<input::Pitch>()
		}
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Profile::axialChord() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Vector chord {tePoint() - lePoint()};

	return mag(chord) * std::sin(angleBetween(chord, Vector::yAxis()));
}


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
	rotateZ(0.5 * pi - stagger.value());

	constrain(reg);
	recompute(reg);
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


Float Profile::chord() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return mag(tePoint() - lePoint());
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


void Profile::inflate(const Float factor) noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Point mid;
	Point topTmp;
	Point botTmp;

	for (auto& [top, bot] : points_)
	{
		mid = midpoint(top, bot);

		topTmp = mid + factor * (top - mid);
		botTmp = mid + factor * (bot - mid);

		top.x() = topTmp.x();
		top.y() = topTmp.y();
		bot.x() = botTmp.x();
		bot.y() = botTmp.y();
	}
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


Float Profile::maxThickness() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Float thickness {0.0};
	for (const auto& [top, bot] : points_)
	{
		thickness = std::max
		(
			thickness,
			mag(top - bot)
		);
	}

	return thickness;
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


Float Profile::passageWidth() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Float xMin {0.0};
	Float xMax {0.0};
	for (const auto& [top, bot] : points_)
	{
		// we know the extrema will be on the top side because
		// the camber is positive (concave camber line)
		if (!isGreaterOrEqual(top.x(), xMin))
			xMin = top.x();
		// NOTE:
		// 		this is probably overkill since the TE is probably the
		// 		farthers point, but fuck it, we'll check anyways
		if (!isLessOrEqual(top.x(), xMin))
			xMax = top.x();
	}

	return xMax - xMin;
}


Profile::Data Profile::points() const noexcept
{
	return points_;
}


Float Profile::radius() const noexcept
{
	return radius_;
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
