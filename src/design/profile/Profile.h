/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Profile

Description
	Class Profile

	NOTE:
		We seem to be introducing a fair bit of numerical error,
		should check ourselves at some point.

SourceFiles
	Profile.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_H
#define DESIGN_PROFILE_H

#include <cmath>

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "Line.h"
#include "Point.h"
#include "ProfileGenerator.h"
#include "Registry.h"
#include "Spline.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class Profile Declaration
\*---------------------------------------------------------------------------*/

class Profile
{
public:

	using Point				= Vector;
	using Data				= Vectorpair<Point>;
	using Iterator			= Data::iterator;
	using Constiterator		= Data::const_iterator;
	using Sizetype			= Data::size_type;
	using Reference			= Data::reference;
	using Constreference	= Data::const_reference;

private:

	// Private data

		// [top, bot]
		Data points_;
		Float radius_;
		bool wrapped_ {false};


	// Member functions

		//- Enforce constraints if any
		void constrain(const input::Registry& reg);

		//- Constrain max thickness
		void constrainMaxThickness(const Float maxAbsBladeThickness) noexcept;

		//- Constrain passage width
		void constrainPassageWidth(const Float maxPassageWidth) noexcept;

		//- Recompute Registry values
		void recompute(const input::Registry& reg);

		//- Rotate around an axis
		//	perm = 0 == x-axis
		//	perm = 1 == y-axis
		//	perm = 2 == z-axis
		template<std::size_t permutation>
		void rotate(const Float angle) noexcept;


public:
	
	// Member functions

		//- Get axial chord length
		[[nodiscard]] Float axialChord() const noexcept(ndebug);

		//- Get TE point pair
		[[nodiscard]] Reference back();

		//- Get TE point pair
		[[nodiscard]] Constreference back() const;

		//- Get iterator to beginning
		[[nodiscard]] Iterator begin();

		//- Get const iterator to beginning
		[[nodiscard]] Constiterator begin() const;

		//- Build geometry
		void build
		(
			const ProfileGenerator& generator,
			const input::Registry& reg
		);

		//- Get the camber line
		[[nodiscard]] std::vector<Point> camberLine() const noexcept(ndebug);

		//- Center on point 'p'
		void centerOn(const Point& p) noexcept;

		//- Get geometric center
		[[nodiscard]] Point centroid() const noexcept;

		//- Get chord length
		[[nodiscard]] Float chord() const noexcept(ndebug);

		//- Check if empty
		[[nodiscard]] bool empty() const noexcept;

		//- Get iterator to end
		[[nodiscard]] Iterator end();

		//- Get const iterator to end
		[[nodiscard]] Constiterator end() const;

		//- Get LE point pair
		[[nodiscard]] Reference front();

		//- Get LE point pair
		[[nodiscard]] Constreference front() const;

		//- Get contour in the form of a single spline
		//	made from top/bot curves ordered as 'getOrderedPoints()'.
		//	Outputs to current model.
		[[nodiscard]] geometry::Spline getContour() const noexcept(ndebug);

		//- Get full contour, ordered [top, bot, tedge].
		//	Curves form a topologically connected loop.
		//	Outputs to current model.
		[[nodiscard]] Sptrvector<geometry::Curve>
		getFullContour() const noexcept(ndebug);

		//- Get geometry points ordered from top (upper) TE to
		//	bot (lower) TE. Outputs to current model.
		[[nodiscard]] std::vector<geometry::Point>
		getPoints() const noexcept(ndebug);

		//- Get trailing edge. Outputs to current model.
		[[nodiscard]] geometry::Line getTrailingEdge() const noexcept(ndebug);

		//- Scale thickness by factor
		void inflate(const Float factor) noexcept(ndebug);

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the leading edge.
		//	The vector points outward with
		//	respect to the profile contour.
		[[nodiscard]] Vector leDirection() const noexcept(ndebug);

		//- Get LE point
		[[nodiscard]] Point lePoint() const noexcept(ndebug);

		//- Get max abs. thickness
		[[nodiscard]] Float maxThickness() const noexcept(ndebug);

		//- Get raw points ordered from top (upper) TE
		//	to bot (lower) TE
		[[nodiscard]] std::vector<Point> orderedPoints() const noexcept;

		//- Get passage width
		[[nodiscard]] Float passageWidth() const noexcept(ndebug);

		//- Get raw data (raw points)
		[[nodiscard]] Data points() const noexcept;

		//- Get radius
		[[nodiscard]] Float radius() const noexcept;

		//- Rotate around x-axis (in radians)
		void rotateX(const Float angle) noexcept;

		//- Rotate around y-axis (in radians)
		void rotateY(const Float angle) noexcept;

		//- Rotate around z-axis (in radians)
		void rotateZ(const Float angle) noexcept;

		//- Uniform scale about centroid
		void scale(const Float factor) noexcept;

		//- Uniform scale about point
		void scale(const Point& p, const Float factor) noexcept;

		//- Get size
		[[nodiscard]] Sizetype size() const noexcept;

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the trailing edge.
		//	The vector points outward with
		//	respect to the profile contour.
		[[nodiscard]] Vector teDirection() const noexcept(ndebug);

		//- Get TE point (midpoint between top/bot TE)
		[[nodiscard]] Point tePoint() const noexcept(ndebug);

		//- Translate by vector 'v'
		void translate(const Vector& v) noexcept;

		//- Wrap to cylinder
		void wrap() noexcept;

		//- Return wrapped state
		[[nodiscard]] bool wrapped() const noexcept;


	// Member operators

		//- Access operator
		[[nodiscard]] Reference operator[](Sizetype pos);

		//- Access operator
		[[nodiscard]] Constreference operator[](Sizetype pos) const;

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<std::size_t permutation>
void Profile::rotate(const Float angle) noexcept
{
	static_assert(permutation >= 0 && permutation <= 2);

	static constexpr std::size_t indices[3]
	{
		(0 + permutation) % 3,
		(1 + permutation) % 3,
		(2 + permutation) % 3
	};

	Float c {std::cos(angle)};
	Float s {std::sin(angle)};

	for (auto& [top, bot] : points_)
	{
		Float top_1 = top[indices[1]];
		Float top_2 = top[indices[2]];
		Float bot_1 = bot[indices[1]];
		Float bot_2 = bot[indices[2]];

		top[indices[1]] = top_1 * c - top_2 * s;
		top[indices[2]] = top_1 * s + top_2 * c;
		bot[indices[1]] = bot_1 * c - bot_2 * s;
		bot[indices[2]] = bot_1 * s + bot_2 * c;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
