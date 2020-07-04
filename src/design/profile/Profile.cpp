/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <cassert>
#include <ostream>
#include <vector>

#include "Profile.h"

#include "CsvWriter.h"
#include "CsvReader.h"
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


void Profile::constrainMaxThickness(const Float thickness) noexcept
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
		isGreaterOrEqual(tMax, thickness)
	)
		inflate
		(
			radius_ * std::asin(0.5 * thickness / radius_) / aMax
		);
}


void Profile::constrainPassageWidth(const Float width) noexcept
{
	Float pw {passageWidth()};
	if
	(
		isGreaterOrEqual(pw, width)
	)
		scale(width / pw);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Profile::Profile
(
	const Path& file,
	const char delimiter,
	const char comment
)
{
	input::CsvReader<Float, Float, Float> csv {delimiter, comment};
	csv.read(file);

	const auto& xCoords {csv.cref<0>()};
	const auto& yCoords {csv.cref<1>()};
	const auto& zCoords {csv.cref<2>()};

	if (xCoords.empty())
		error(FUNC_INFO, "profile point coordinate list empty");
	else if (xCoords.size() % 2 == 0)
		error
		(
			FUNC_INFO,
			"even number of profile point coordinates given, should be odd"
		);

	auto numPoints {xCoords.size() / 2 + 1};
	points_.reserve(numPoints);

	auto topCount {numPoints - 1};
	auto botCount {numPoints - 1};

	for (auto i {0ul}; i < numPoints; ++i)
	{
		points_.emplace_back
		(
			Point
			{
				xCoords[topCount],
				yCoords[topCount],
				zCoords[topCount]
			},
			Point
			{
				xCoords[botCount],
				yCoords[botCount],
				zCoords[botCount]
			}
		);

		--topCount;
		++botCount;
	}

	// check and get radius
	auto le {lePoint()};

	if (!valid())
	{
		wrapped_ = true;

		if (!valid())
			error(FUNC_INFO, "invalid profile");

		radius_ = std::hypot(le.y(), le.z());
	}
	else
		radius_ = le.z();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Profile::axialChord() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	Vector chord {tePoint() - lePoint()};

	return mag(chord) * std::sin(angleBetween(chord, Vector::yAxis()));
}


Profile::reference Profile::back()
{
	return points_.back();
}


Profile::const_reference Profile::back() const
{
	return points_.back();
}


Profile::iterator Profile::begin()
{
	return points_.begin();
}


Profile::const_iterator Profile::begin() const
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
}


Float Profile::camberAngle() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return outletAngle() - inletAngle();
}


std::vector<Profile::Point> Profile::camberLinePoints() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	std::vector<Profile::Point> camberLine;
	camberLine.reserve(points_.size());

	if (!wrapped_)
		for (const auto& [top, bot] : points_)
			camberLine.emplace_back
			(
				midpoint(top, bot)
			);
	else
	{
		for (const auto& [top, bot] : points_)
		{
			auto tmp {projectionYZ(top)};
			auto ang
			{
				0.5 * angleBetween(tmp, projectionYZ(bot))
			};

			tmp.rotateX(ang);

			camberLine.emplace_back
			(
				0.5 * (top.x() + bot.x()),
				tmp.y(),
				tmp.z()
			);
		}
	}

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


Profile::iterator Profile::end()
{
	return points_.end();
}


Profile::const_iterator Profile::end() const
{
	return points_.end();
}


Profile::reference Profile::front()
{
	return points_.front();
}


Profile::const_reference Profile::front() const
{
	return points_.front();
}


geometry::Spline Profile::getCamberLine() const noexcept(ndebug)
{
	return geometry::Spline {camberLinePoints()};
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


Float Profile::inletAngle() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return pi - angleBetween(leDirection(), Vector::yAxis());
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


Float Profile::outletAngle() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return angleBetween(teDirection(), Vector::yAxis());
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


Profile::size_type Profile::size() const noexcept
{
	return points_.size();
}



Float Profile::staggerAngle() const noexcept(ndebug)
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	return angleBetween(tePoint() - lePoint(), Vector::yAxis());
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


void Profile::unwrap() noexcept
{
	if (!wrapped_)
		return;

	for (auto& [top, bot] : points_)
	{
		Float aTop {top.y() / radius_};
		Float aBot {bot.y() / radius_};

		top.y() = radius_ * std::asin(aTop);
		top.z() = radius_ * std::acos(aTop);
		bot.y() = radius_ * std::asin(aBot);
		bot.z() = radius_ * std::acos(aBot);
	}

	wrapped_ = false;
}


bool Profile::valid() const
{
	if (empty())
		error(FUNC_INFO, "profile not built");

	bool check {true};

	if (!wrapped_)
		for (const auto& [top, bot] : points_)
			check = check && tolerance(top.z(), bot.z(), eps);
	else
	{
		auto le {lePoint()};
		auto radius {std::hypot(le.y(), le.z())};

		for (const auto& [top, bot] : points_)
			check = check
				 && tolerance(radius, std::hypot(top.y(), top.z()), eps)
				 && tolerance(radius, std::hypot(bot.y(), bot.z()), eps);
	}

	return check;
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


void Profile::writeCsv(const Path& file) const
{
	CsvWriter csv {file};
	csv.writeComment("ordering: TE (top) - LE - TE (bot)");
	csv.writeHeader("x", "y", "z");

	for (const auto& p : orderedPoints())
		csv.write(p.x(), p.y(), p.z());
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

Profile::reference Profile::operator[](size_type pos)
{
	return points_[pos];
}


Profile::const_reference Profile::operator[](size_type pos) const
{
	return points_[pos];
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
