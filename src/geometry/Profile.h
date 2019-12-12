/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Profile

Description
	Class Profile

SourceFiles
	Profile.cpp

\*---------------------------------------------------------------------------*/

#ifndef PROFILE_H
#define PROFILE_H

#include <vector>

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

/*---------------------------------------------------------------------------*\
						Class Profile Declaration
\*---------------------------------------------------------------------------*/

class Profile
{
private:

	typedef std::vector<PointCoordinates> Pcvector;
	typedef Pcvector::iterator Iterator;
	typedef Pcvector::const_iterator Constiterator;


	// Private data

		Pcvector points_;

		bool wrapped_ {false};
		static constexpr PointCoordinates origin_ {0.0, 0.0, 0.0};


	// Member functions

		//- 2d rotate around z-axis positioned at origin (in degrees)
		void rotate(const double angle);

		//- 2d uniform scale about origin
		void scale(const double factor);

		//- Translate from center to 'coordinates'
		void translate(const PointCoordinates& coordinates) noexcept;


public:
	
	// Constructors

		//- Construct from input
		Profile() = default;

		//- Copy constructor
		Profile(const Profile&) = default;

		//- Move constructor
		Profile(Profile&&) = default;


	//- Destructor
	~Profile() = default;


	// Member functions

		//- Get iterator to beginning
		Iterator begin();

		//- Get const iterator to beginning
		Constiterator begin() const;

		//- Build geometry
		void build
		(
			const ProfileGenerator& generator,
			const double chord,
			const double radius,
			const double stagger
		);

		//- Check if empty
		bool empty() const noexcept;

		//- Get iterator to end
		Iterator end();

		//- Get const iterator to end
		Constiterator end() const;

		//- Get geometric center
		PointCoordinates getCenter() const noexcept;

		//- Get contour
		Spline getContour() const;	

		//- Get points
		std::vector<Point> getPoints() const noexcept;

		//- Get trailing edge
		Line getTrailingEdge() const;

		//- Return wrapped state
		bool isWrapped() const noexcept;

		//- Get size
		Pcvector::size_type size() const noexcept;

		//- Wrap to cylinder
		void wrap() noexcept;


	// Member operators

		//- Disallow assignment
		Profile& operator=(const Profile&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
