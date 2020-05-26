/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Surface

Description
	A base class for surface geometry classes.

	WARNING:
		We don't check whether the supplied curves form a loop.
		We also do not check whether the assumed loop is made of curves
		with topologically identical end points i.e. whether two neighbouring
		curves within the loop join at a single topological point.

		This is an issue because gmsh will create an additional wire
		if the surface is created from curves with arbitrary end points
		and fuck up our tag count i.e. crash. It will also crash if
		the curves don't actually form a loop.

		The real kicker is that the created wire isn't part of the surface
		boundary.

		Godspeed.

SourceFiles
	Surface.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_SURFACE_H
#define GEOMETRY_SURFACE_H

#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

#include "Curve.h"
#include "Entity.h"
#include "Error.h"
#include "General.h"
#include "PlaceholderSurface.h"
#include "Point.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Type traits * * * * * * * * * * * * * * * * //

template<typename T>
inline constexpr bool isCurveSptr_v = std::is_same_v
<
	Sptr<Curve>,
	removeCVRef_t<T>
>;


/*---------------------------------------------------------------------------*\
						Class Surface Declaration
\*---------------------------------------------------------------------------*/

class Surface
:
	public Shape<Entity2D>
{
private:

	// Private data

		Sptrvector<Curve> boundary_;
		Uptr<std::vector<Sptrvector<Curve>>> holes_ {nullptr};

		Uptr<Sptrvector<Point>> corners_ {nullptr};


protected:

	template<typename T>
	inline static constexpr bool isValid_v =
		isCurveSptr_v<T>
	 || std::is_base_of_v<Curve, removeCVRef_t<T>>;


	// Constructors

		//- Default constructor
		Surface() = default;

		//- Construct from curves forming a closed loop
		//	FIXME: should check wheather the curves form a loop
		template
		<
			typename... Curves,
			typename = std::enable_if_t<(isValid_v<Curves> && ...)>
		>
		Surface(Curves&&... cs);

		//- Construct from vectors of curves (curve sptrs) forming closed loops,
		//	the first vector is the boundary, the rest are boundaries
		//	of holes within the surface
		//	FIXME: should check wheather the curves form a loop
		template
		<
			typename Boundary,
			typename... Holes,
			typename = std::enable_if_t
			<
				std::is_same_v
				<
					Sptrvector<Curve>,
					removeCVRef_t<Boundary>
				>
			>
		>
		Surface(Boundary&& b, Holes&&... hs);


public:

	// Constructors

		//- Construct from a placeholder surface
		Surface(const detail::PlaceholderSurface& s);

		//- Copy constructor
		Surface(const Surface&) = delete;

		//- Move constructor
		Surface(Surface&&) = default;


	//- Destructor
	virtual ~Surface() noexcept;


	// Member functions

		//- Get the boundary curves
		[[nodiscard]] const Sptrvector<Curve>& boundaryCRef() const noexcept;

		//- Get the boundary curves
		[[nodiscard]] Sptrvector<Curve>& boundaryRef() noexcept;

		//- Get the corner points
		[[nodiscard]] const Sptrvector<Point>&
		cornersCRef() const noexcept(ndebug);

		//- Get the corner points
		[[nodiscard]] Sptrvector<Point>& cornersRef() noexcept(ndebug);

		//- Get the hole curves
		[[nodiscard]] const std::vector<Sptrvector<Curve>>&
		holesCRef() const noexcept(ndebug);

		//- Get the hole curves
		[[nodiscard]] std::vector<Sptrvector<Curve>>&
		holesRef() noexcept(ndebug);

		//- Check if corners have been assigned
		[[nodiscard]] bool hasCorners() const noexcept;

		//- Check the surface has holes
		[[nodiscard]] bool hasHoles() const noexcept;

		//- Store corner points (3 or 4 points only)
		template
		<
			typename... Points,
			typename = std::enable_if_t<(isPointSptr_v<Points> && ...)>
		>
		void storeCorners(Points&&... ps);


	// Member operators

		//- Disallow copy assignment
		Surface& operator=(const Surface&) = delete;

		//- Disallow move assignment
		Surface& operator=(Surface&&) = delete;

};


// * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * * //

template<typename... Curves, typename>
Surface::Surface(Curves&&... cs)
{
	// FIXME: sanity check missing (check if curves form a closed loop)

	auto&& makeSptr = [](auto&& curve)
	{
		using CurveType = decltype(curve);

		if constexpr (isCurveSptr_v<CurveType>)
		{
			return curve;
		}
		else
			return Sptr<Curve>
			{
				new removeCVRef_t<CurveType>
				{
					std::forward<CurveType>(curve)
				}
			};
	};

	boundary_.reserve(sizeof...(cs));

	(
		boundary_.emplace_back
		(
			makeSptr(std::forward<Curves>(cs))
		), ...
	);
}


template<typename Boundary, typename... Holes, typename>
Surface::Surface(Boundary&& b, Holes&&... hs)
:
	boundary_
	{
		std::forward<Boundary>(b)
	}
{
	if constexpr (sizeof...(hs) != 0)
	{
		static_assert
		(
			(std::is_same_v<Sptrvector<Curve>, removeCVRef_t<Holes>> && ...)
		);

		holes_.reset
		(
			new std::vector<Sptrvector<Curve>> {}
		);
		holes_->reserve(sizeof...(hs));

		(holes_->emplace_back(std::forward<Holes>(hs)), ...);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename... Points, typename>
void Surface::storeCorners(Points&&... ps)
{
	static_assert
	(
		sizeof...(Points) == 3
	 || sizeof...(Points) == 4
	);

	assert(!corners_);

	// sanity check
	auto match = [&](const auto& point)
	{
		bool contained {false};

		for (const auto& b : boundary_)
		{
			contained = b->startRef().tag() == point->tag()
					 || b->endRef().tag() == point->tag();

			if (contained)
				return contained;
		}
		return contained;
	};

	if
	(
		!(match(ps) && ...)
	)
		error(FUNC_INFO, "tried to assign nonexistent corner point");

	corners_.reset
	(
		new Sptrvector<Point> {}
	);
	corners_->reserve(sizeof...(Points));

	(corners_->push_back(std::forward<Points>(ps)), ...);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
