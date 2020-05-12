/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::detail::PlaceholderShape

Description
	PlaceholderShape class

	A geometry placeholder virtual base class.
	The placeholder classes are used by geometry module classes when raw kernel
	data needs to be converted into usable classes.

SourceFiles
	PlaceholderShape.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_PLACEHOLDER_SHAPE_H
#define GEOMETRY_DETAIL_PLACEHOLDER_SHAPE_H

#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

/*---------------------------------------------------------------------------*\
						Class PlaceholderShape Declaration
\*---------------------------------------------------------------------------*/

class PlaceholderShape
{
protected:

	// Constructors

		//- Construct from a tag
		explicit PlaceholderShape(const std::size_t t) noexcept;


public:

	// Public data

		const std::size_t tag;


	//- Destructor
	virtual ~PlaceholderShape() = default;

};


// * * * * * * * * * * * * * * * Type Traits * * * * * * * * * * * * * * * * //

template<typename T>
inline constexpr bool isPlaceholder_v = std::is_base_of_v
<
	PlaceholderShape, removeCVRef_t<T>
>;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
