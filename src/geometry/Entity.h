/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Entity

Description
	Base class template for geometry objects.

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_ENTITY_H
#define GEOMETRY_ENTITY_H

#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
						Class Entity Declaration
\*---------------------------------------------------------------------------*/

template<Integer dimension>
class Entity
{
private:

	static_assert(dimension >= 0 && dimension <= 3);


	// Private data

		inline static thread_local std::size_t count_ {0};


protected:

	// Protected data

		// using tag_ == 0 as a flag for not owning geometry
		std::size_t tag_;


	// Constructors

		//- Default constructor
		Entity() noexcept;

		//- Construct from a tag
		Entity(const std::size_t tag) noexcept;


public:

	// Public data

		inline static constexpr Integer dim {dimension};


	// Constructors

		//- Disallow copy construction
		Entity(const Entity&) = delete;

		//- Move constructor
		Entity(Entity&&) noexcept;


	//- Destructor
	virtual ~Entity() = default;


	// Member functions

		//- Get tag
		constexpr std::size_t tag() const noexcept;

		//- Get number of created entities
		static constexpr std::size_t count() noexcept;


	// Member operators

		//- Disallow copy assignment
		Entity& operator=(const Entity&) = delete;

		//- Disallow move assignment
		Entity& operator=(Entity&&) = delete;

};

// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<Integer dimension>
Entity<dimension>::Entity() noexcept
:
	tag_
	{
		++(this->count_)
	}
{}


template<Integer dimension>
Entity<dimension>::Entity(const std::size_t tag) noexcept
:
	tag_ {tag}
{
	// sync count_ with tag_, so we don't assign an
	// already existing tag in the future
	while(this->count_ < this->tag_)
		++(this->count_);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<Integer dimension>
Entity<dimension>::Entity(Entity&& e) noexcept
:
	tag_ {e.tag_}
{
	e.tag_ = 0;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<Integer dimension>
constexpr std::size_t Entity<dimension>::tag() const noexcept
{
	return this->tag_;
}


template<Integer dimension>
constexpr std::size_t Entity<dimension>::count() noexcept
{
	return Entity<dimension>::count_;
}


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

using Entity0D = Entity<0>;
using Entity1D = Entity<1>;
using Entity2D = Entity<2>;
using Entity3D = Entity<3>;


template<typename T, Integer dimension>
inline static constexpr bool isND_v = std::is_base_of_v<Entity<dimension>, T>;


template<typename T>
inline static constexpr bool is0D_v = isND_v<T, 0>;


template<typename T>
inline static constexpr bool is1D_v = isND_v<T, 1>;


template<typename T>
inline static constexpr bool is2D_v = isND_v<T, 2>;


template<typename T>
inline static constexpr bool is3D_v = isND_v<T, 3>;


template<typename T>
inline static constexpr bool isEntity_v = is0D_v<T>
									   || is1D_v<T>
									   || is2D_v<T>
									   || is3D_v<T>;


//- Return an entity of order lowered by 1.
//	0-order entities return themselves.
template
<
	typename T,
	typename = std::enable_if_t<isEntity_v<T>>
>
struct LowerOrderEntity
{
	using type = Entity<T::dim - 1>;
};


template<>
struct LowerOrderEntity<Entity0D>
{
	using type = Entity0D;
};


template<typename T>
using LowerOrderEntity_t = typename LowerOrderEntity<T>::type;


//- Return an entity of order higher by 1.
//	3-order entities return themselves.
template
<
	typename T,
	typename = std::enable_if_t<isEntity_v<T>>
>
struct HigherOrderEntity
{
	using type = Entity<T::dim + 1>;
};


template<>
struct HigherOrderEntity<Entity3D>
{
	using type = Entity3D;
};


template<typename T>
using HigherOrderEntity_t = typename HigherOrderEntity<T>::type;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
