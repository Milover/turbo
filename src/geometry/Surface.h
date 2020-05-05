/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Surface

Description
	A base class for surface geometry classes.

	NOTE: construction with holes unimplemented!

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
	inline static constexpr bool isValid_v = isCurveSptr_v<T>
										  || std::is_base_of_v<Curve, T>;

	template<typename T>
	using enableIfValid_t = std::enable_if_t<isValid_v<T>>;


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


public:

	// Constructors

		//- Construct from a placeholder surface
		Surface(const detail::PlaceholderSurface& s);

		//- Copy constructor
		Surface(const Surface&) = delete;

		//- Move constructor
		Surface(Surface&&) = default;


	//- Destructor
	virtual ~Surface() = default;


	// Member functions

		//- Get the boundary curves
		[[nodiscard]] Sptrvector<Curve>& boundaryRef() noexcept;

		//- Get the corner points
		[[nodiscard]] Sptrvector<Point>& cornersRef() noexcept(ndebug);

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
		using curveType = decltype(curve);

		if constexpr (isCurveSptr_v<curveType>)
		{
			return curve;
		}
		else
			return Sptr<Curve>
			{
				new removeCVRef_t<curveType>
				{
					std::forward<curveType>(curve)
				}
			};
	};

	boundary_.reserve(sizeof...(Curves));

	(
		boundary_.push_back
		(
			makeSptr(std::forward<Curves>(cs))
		), ...
	);
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
