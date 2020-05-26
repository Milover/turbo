/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::operators::Extrude

Description
	Extrude class

SourceFiles
	Extrude.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_OPERATORS_EXTRUDE_H
#define GEOMETRY_OPERATORS_EXTRUDE_H

#include <cassert>
#include <type_traits>

#include "Entity.h"
#include "General.h"
#include "GeometryDetailGeneral.h"
#include "GmshExtrude.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace operators
{

/*---------------------------------------------------------------------------*\
						Class Extrude Definition
\*---------------------------------------------------------------------------*/

class Extrude
{
private:

	template<typename T>
	inline static constexpr bool isValid_v =
		isSptr_v<T>
	 || (
			std::is_rvalue_reference_v<T>
		 || (
				std::is_class_v<T>
			 && !std::is_const_v<T>
			)
	 	);

	// Private data

		//- The position of the extrusion in the returned vector of tags
		inline static constexpr std::size_t pos_ {1};


	// Member functions

		//- Execute extrusion
		template<typename Ptr>
		[[nodiscard]] auto execute
		(
			Ptr&& p,
			const Vector& v
		) const;

public:

		//- Create an extrusion
		template
		<
			typename Geometry,
			typename = std::enable_if_t<isValid_v<Geometry>>
		>
		[[nodiscard]] auto operator()
		(
			Geometry&& g,
			const Vector& direction
		) const;

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename Ptr>
auto Extrude::execute
(
	Ptr&& p,
	const Vector& v
) const
{
	using GeometryType = detail::GeometryHigherOrderType_t
	<
		typename removeCVRef_t<Ptr>::element_type
	>;

	auto tags
	{
		interface::GmshExtrude {}(p.get(), v)
	};

	detail::GeometryPlaceholderType_t<GeometryType> placeholder {tags[pos_]};

	placeholder.tryStore(p);

	return GeometryType {placeholder};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename Geometry, typename>
auto Extrude::operator()
(
	Geometry&& g,
	const Vector& direction
) const
{
	if constexpr (isSptr_v<Geometry>)
	{
		using GeometryType = typename removeCVRef_t<Geometry>::element_type;

		static_assert(isEntity_v<GeometryType>);
		static_assert
		(
			GeometryType::dim < Entity3D::dim
		);

		return execute
		(
			std::forward<Geometry>(g),
			direction
		);
	}
	else
	{
		static_assert(isEntity_v<Geometry>);
		static_assert
		(
			removeCVRef_t<Geometry>::dim < Entity3D::dim
		);

		return execute
		(
			Sptr<detail::GeometryBaseType_t<Geometry>>
			{
				new removeCVRef_t<Geometry> {std::forward<Geometry>(g)}
			},
			direction
		);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace operators
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
