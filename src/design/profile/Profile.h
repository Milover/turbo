/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Profile

Description
	Class Profile

SourceFiles
	Profile.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_H
#define DESIGN_PROFILE_H

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
private:

	using Point			= Vector;
	using Iterator		= Vectorpair<Point>::iterator;
	using Constiterator	= Vectorpair<Point>::const_iterator;
	using Sizetype		= Vectorpair<Point>::size_type;


	// Private data

		Vectorpair<Point> points_;

		bool wrapped_ {false};


	// Member functions

		//- Center on point 'p'
		void centerOn(const Point& p) noexcept;

		//- 2d rotate around z-axis positioned (in radians)
		void rotate2D(const Float angle) noexcept;

		//- Uniform scale about centroid
		void scale(const Float factor) noexcept;

		//- Uniform scale about point
		void scale(const Point& p, const Float factor) noexcept;

		//- Translate by vector 'v'
		void translate(const Vector& v) noexcept;


public:
	
	// Member functions

		//- Get iterator to beginning
		Iterator begin();

		//- Get const iterator to beginning
		Constiterator begin() const;

		//- Build geometry
		void build
		(
			const ProfileGenerator& generator,
			const input::Registry& reg
		);

		//- Get the camber line
		std::vector<Point> camberLine() const noexcept(ndebug);

		//- Get geometric center
		Point centroid() const noexcept;

		//- Check if empty
		bool empty() const noexcept;

		//- Get iterator to end
		Iterator end();

		//- Get const iterator to end
		Constiterator end() const;

		//- Get contour. Outputs to current model.
		geometry::Spline getContour() const noexcept(ndebug);

		//- Get geometry points ordered from top (upper) TE to
		//	bot (lower) TE. Outputs to current model.
		std::vector<geometry::Point> getPoints() const noexcept(ndebug);

		//- Get trailing edge. Outputs to current model.
		geometry::Line getTrailingEdge() const noexcept(ndebug);

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the leading edge.
		//	The vector points outward with
		//	respect to the profile contour.
		Vector leDirection() const noexcept(ndebug);

		//- Get LE point
		Point lePoint() const noexcept(ndebug);

		//- Get raw points ordered from top (upper) TE
		//	to bot (lower) TE
		std::vector<Point> orderedPoints() const noexcept;

		//- Get raw data (raw points)
		Vectorpair<Point> points() const noexcept;

		//- Get size
		Sizetype size() const noexcept;

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the trailing edge.
		//	The vector points outward with
		//	respect to the profile contour.
		Vector teDirection() const noexcept(ndebug);

		//- Get TE point
		Point tePoint() const noexcept(ndebug);

		//- Wrap to cylinder
		void wrap() noexcept;

		//- Return wrapped state
		bool wrapped() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
