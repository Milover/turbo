/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Curve

Description
	A base class for curve geometry classes.

SourceFiles
	Curve.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_CURVE_H
#define GEOMETRY_CURVE_H

#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

#include "Entity.h"
#include "General.h"
#include "PlaceholderCurve.h"
#include "Point.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Type traits * * * * * * * * * * * * * * * * //

template<typename T>
inline constexpr bool isPointSptr_v = std::is_same_v
<
	Sptr<Point>,
	removeCVRef_t<T>
>;


/*---------------------------------------------------------------------------*\
						Class Curve Declaration
\*---------------------------------------------------------------------------*/

class Curve
:
	public Shape<Entity1D>
{
private:

	// Private data

		Sptr<Point> start_ {nullptr};
		Sptr<Point> end_ {nullptr};


protected:

	using Coordvector = std::vector<Coordinates>;
	using Pointvector = std::vector<Point>;

	template<typename T>
	using enableIfValid_t = std::enable_if_t
	<
		isPointSptr_v<T>
	 || std::is_same_v<Coordinates, removeCVRef_t<T>>
	 || std::is_same_v<Point, T>
	 || std::is_same_v<Point&&, T>
	>;


	// Constructors

		//- Default constructor
		Curve() = default;

		//- Construct from start/end point shared pointers
		template<typename T1, typename T2>
		Curve(T1&& start, T2&& end);


	// Member functions

		//- Store end point, only if end is not set
		template
		<
			typename T,
			typename = enableIfValid_t<T>
		>
		void storeEnd(T&& end);

		//- Store start point, only if start is not set
		template
		<
			typename T,
			typename = enableIfValid_t<T>
		>
		void storeStart(T&& start);

		//- Store start/end points, only if start/end are not set
		template<typename T1, typename T2>
		void storeStartAndEnd(T1&& start, T2&& end);


public:

	// Constructors

		//- Construct from a placeholder curve
		Curve(const detail::PlaceholderCurve& c);

		//- Copy constructor
		Curve(const Curve&) = delete;

		//- Move constructor
		Curve(Curve&&) = default;


	//- Destructor
	virtual ~Curve() noexcept;


	// Member functions

		//- Get a shared pointer to the end point
		[[nodiscard]] Sptr<Point> endPtr() const noexcept;

		//- Get a const reference to the end point
		[[nodiscard]] const Point& endRef() const noexcept;

		//- Get a shared pointer to the start point
		[[nodiscard]] Sptr<Point> startPtr() const noexcept;

		//- Get a const reference to the start point
		[[nodiscard]] const Point& startRef() const noexcept;


	// Member operators

		//- Disallow copy assignment
		Curve& operator=(const Curve&) = delete;

		//- Disallow move assignment
		Curve& operator=(Curve&&) = delete;

};

// * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * * //

template<typename T1, typename T2>
Curve::Curve(T1&& start, T2&& end)
{
	storeStartAndEnd
	(
		std::forward<T1>(start),
		std::forward<T2>(end)
	);
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T, typename>
void Curve::storeEnd(T&& end)
{
	assert(!end_);

	if constexpr (isPointSptr_v<T>)
		end_ = std::forward<T>(end);
	else
		end_.reset
		(
			new Point {std::forward<T>(end)}
		);
}


template<typename T, typename>
void Curve::storeStart(T&& start)
{
	assert(!start_);

	if constexpr (isPointSptr_v<T>)
		start_ = std::forward<T>(start);
	else
		start_.reset
		(
			new Point {std::forward<T>(start)}
		);
}


template<typename T1, typename T2>
void Curve::storeStartAndEnd(T1&& start, T2&& end)
{
	storeStart(std::forward<T1>(start));
	storeEnd(std::forward<T2>(end));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
