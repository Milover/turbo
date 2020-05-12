/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::mesh::Group

Description
	Class template for groups of geometry.

\*---------------------------------------------------------------------------*/

#ifndef MESH_GROUP_H
#define MESH_GROUP_H

#include <utility>
#include <type_traits>

#include "Entity.h"
#include "General.h"
#include "GeometryDetailGeneral.h"
#include "GmshPhysicalGroup.h"
#include "GmshRemovePhysicalGroup.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// Forward declarations
namespace interface
{
	class GmshPhysicalGroup;
	class GmshRemovePhysicalGroup;
}

namespace mesh
{

/*---------------------------------------------------------------------------*\
						Class Group Declaration
\*---------------------------------------------------------------------------*/

template<typename Geometry>
class Group final
{
private:

	static_assert(geometry::isEntity_v<Geometry>);

	template<typename T>
	inline static constexpr bool isValid_v = std::is_same_v
	<
		Sptr<Geometry>, removeCVRef_t<T>
	>;

	using Subgroup = Group
	<
		geometry::detail::GeometryLowerOrderType_t<Geometry>
	>;


	// Private data

		std::size_t tag_;
		String name_;

		Sptrvector<Geometry> geometry_;
		Sptrvector<Subgroup> subgroups_;


public:

	using type = Geometry;


	// Constructors

		//- Construct from a name, geometry and subgroups
		template
		<
			typename... Ptrs,
			typename = std::enable_if_t<(isValid_v<Ptrs> && ...)>
		>
		Group(const String& name, Ptrs&&... ps) noexcept;

		//- Disallow copy construction
		Group(const Group&) = delete;

		//- Move constructor
		Group(Group&&) = default;


	//- Destructor
	~Group() noexcept;


	// Member functions

		//- Get dimension
		[[nodiscard]] constexpr Integer dim() const noexcept;

		//- Get tag
		[[nodiscard]] std::size_t tag() const noexcept;

		//- Get patch name
		[[nodiscard]] String name() const noexcept;

		//- Get geometry which defines the group
		[[nodiscard]] const Sptrvector<Geometry>& geometryCRef() const noexcept;

		//- Get geometry which defines the group
		[[nodiscard]] Sptrvector<Geometry>& geometryRef() noexcept;

		//- Get the subgroups
		[[nodiscard]] const Sptrvector<Subgroup>&
		subgroupsCRef() const noexcept;

		//- Store subgroups
		template
		<
			typename SGrps,
			typename = std::enable_if_t
			<
				std::is_same_v<Sptrvector<Subgroup>, removeCVRef_t<SGrps>>
			>
		>
		void storeSubgroups(SGrps&& subgroups) noexcept;

		//- Get the subgroups
		[[nodiscard]] Sptrvector<Subgroup>& subgroupsRef() noexcept;


	// Member operators

		//- Disallow copy assignment
		Group& operator=(const Group&) = delete;

		//- Disallow move assignment
		Group& operator=(Group&&) = delete;

};

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename Geometry>
template<typename... Ptrs, typename>
Group<Geometry>::Group(const String& name, Ptrs&&... ps) noexcept
:
	name_ {name}
{
	this->geometry_.reserve(sizeof...(ps));

	(this->geometry_.emplace_back(std::forward<Ptrs>(ps)), ...);

	this->tag_ = interface::GmshPhysicalGroup {}(this, this->geometry_);
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<typename Geometry>
Group<Geometry>::~Group() noexcept
{
	if (this->tag_ != 0)
	{
		interface::GmshRemovePhysicalGroup {}(this);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename Geometry>
constexpr Integer Group<Geometry>::dim() const noexcept
{
	return Geometry::dim;
}


template<typename Geometry>
String Group<Geometry>::name() const noexcept
{
	return this->name_;
}


template<typename Geometry>
const Sptrvector<Geometry>& Group<Geometry>::geometryCRef() const noexcept
{
	return this->geometry_;
}


template<typename Geometry>
Sptrvector<Geometry>& Group<Geometry>::geometryRef() noexcept
{
	return this->geometry_;
}


template<typename Geometry>
template<typename SGrps, typename>
void Group<Geometry>::storeSubgroups(SGrps&& subgroups) noexcept
{
	this->subgroups_ = std::forward<SGrps>(subgroups);
}


template<typename Geometry>
const Sptrvector<typename Group<Geometry>::Subgroup>&
Group<Geometry>::subgroupsCRef() const noexcept
{
	return this->subgroups_;
}


template<typename Geometry>
Sptrvector<typename Group<Geometry>::Subgroup>&
Group<Geometry>::subgroupsRef() noexcept
{
	return this->subgroups_;
}



template<typename Geometry>
std::size_t Group<Geometry>::tag() const noexcept
{
	return this->tag_;
}


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

//- Check if a type is a Group
template<typename T, typename = void>
struct isGroup : std::false_type {};

template<typename T>
struct isGroup<T, std::void_t<typename removeCVRef_t<T>::type>>
:
	std::bool_constant
	<
		std::is_same_v
		<
			Group<typename removeCVRef_t<T>::type>,
			removeCVRef_t<T>
		>
	>
{};

template<typename T>
inline constexpr bool isGroup_v = isGroup<T>::value;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace mesh
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
