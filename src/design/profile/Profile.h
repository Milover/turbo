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

#include <vector>

#include "General.h"
#include "Geometry.h"
#include "ProfileGenerator.h"
#include "Variables.h"
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
			const input::Chord& chord,
			const input::Radius& radius,
			const input::StaggerAngle& stagger
		);

		//- Check if empty
		bool empty() const noexcept;

		//- Get iterator to end
		Iterator end();

		//- Get const iterator to end
		Constiterator end() const;

		//- Get geometric center
		Point centroid() const noexcept;

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the leading edge.
		//	The vector points outward with
		//	respect to the profile contour.
		Vector leDirection() const;

		//- Get LE point
		Vector lePoint() const;

		//- Get contour
		geometry::Spline getContour() const;

		//- Get points ordered from top (upper) TE to
		//	bot (lower) TE
		std::vector<geometry::Point> getPoints() const;

		//- Get trailing edge
		geometry::Line getTrailingEdge() const;

		//- Get data (raw points)
		Vectorpair<Point> points() const noexcept;

		//- Get size
		Sizetype size() const noexcept;

		//- Get the unit direction vector
		//	of the camberline tangent at
		//	the trailing edge.
		//	The vector points outward with
		//	respect to the profile contour.
		Vector teDirection() const;

		//- Get TE point
		Vector tePoint() const;

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
