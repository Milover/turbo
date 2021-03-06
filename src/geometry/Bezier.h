/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Bezier

Description
	Bezier class

SourceFiles
	Bezier.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_BEZIER_H
#define GEOMETRY_BEZIER_H

#include <cassert>
#include <type_traits>
#include <utility>

#include "Curve.h"
#include "General.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Bezier Declaration
\*---------------------------------------------------------------------------*/

class Bezier final
:
	public Curve
{
private:

	// Member functions

		//- Construct spline geometry
		void construct(const Pointvector& points) const noexcept;


public:

	// Constructors

		//- Construct from a vector of coordinates
		Bezier(const Coordvector& pts);

		//- Construct from a vector of coordinates,
		//	use 'start' as the start point.
		//	NOTE: 'coords' should contain all of the points
		//	needed to define the spline
		template<typename T>
		Bezier
		(
			T&& start,
			const Coordvector& coords
		);

		//- Construct from a vector of coordinates,
		//	use 'end' as the end point.
		//	NOTE: 'coords' should contain all of the points
		//	needed to define the spline
		template<typename T>
		Bezier
		(
			const Coordvector& coords,
			T&& end
		);

		//- Construct from a vector of coordinates,
		//	use 'start' as the start point and 'end' as the end point.
		//	NOTE: 'coords' should contain all of the points
		//	needed to define the spline
		template<typename T1, typename T2>
		Bezier
		(
			T1&& start,
			const Coordvector& coords,
			T2&& end
		);

		//- Copy constructor
		Bezier(const Bezier&) = delete;

		//- Copy constructor
		Bezier(Bezier&&) = default;


	//- Destructor
	~Bezier() = default;


	// Member operators

		//- Disallow copy assignment
		Bezier& operator=(const Bezier&) = delete;

		//- Disallow copy assignment
		Bezier& operator=(Bezier&&) = delete;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
Bezier::Bezier
(
	T&& start,
	const Coordvector& coords
)
:
	Bezier
	{
		std::forward<T>(start),
		coords,
		coords.back()
	}
{}


template<typename T>
Bezier::Bezier
(
	const Coordvector& coords,
	T&& end
)
:
	Bezier
	{
		coords.front(),
		coords,
		std::forward<T>(end)
	}
{}


template<typename T1, typename T2>
Bezier::Bezier
(
	T1&& start,
	const Coordvector& coords,
	T2&& end
)
:
	Curve
	{
		std::forward<T1>(start),
		std::forward<T2>(end)
	}
{
	// sanity check
	assert(startRef().coordinates() == coords.front());
	assert(endRef().coordinates() == coords.back());

	std::vector<Point> points;
	points.reserve(coords.size() - 2);

	// skip start/end because we have (stored) them already
	for (auto it {coords.begin() + 1}; it != coords.end() - 1; ++it)
		points.push_back(Point {*it});

	construct(points);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
