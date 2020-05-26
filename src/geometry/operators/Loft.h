/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::operators::Loft

Description
	Loft class

SourceFiles
	Loft.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_OPERATORS_LOFT_H
#define GEOMETRY_OPERATORS_LOFT_H

#include <cassert>
#include <type_traits>

#include "Curve.h"
#include "General.h"
#include "GmshLoft.h"
#include "PlaceholderSurface.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace operators
{

/*---------------------------------------------------------------------------*\
						Class Loft Definition
\*---------------------------------------------------------------------------*/

class Loft
{
private:

	template<typename T>
	inline static constexpr bool isValid_v =
		std::is_same_v<Sptr<Curve>, removeCVRef_t<T>>
	 || std::is_base_of_v<Curve, removeCVRef_t<T>>;


	// Private data

		//- The position of the loft in the returned vector of tags
		inline static constexpr std::size_t pos_ {0};


	// Member functions

		//- Execute loft
		template<typename Curvevector>
		[[nodiscard]] Surface execute(Curvevector&& cv) const;


public:

		//- Create an lofted surface
		template
		<
			typename... Curves,
			typename = std::enable_if_t<(isValid_v<Curves> && ...)>
		>
		[[nodiscard]] Surface operator()(Curves&&... cs) const;

		//- Create an lofted surface
		template
		<
			typename Curves,
			typename = std::enable_if_t
			<
				std::is_same_v<Sptrvector<Curve>, removeCVRef_t<Curves>>
			>
		>
		[[nodiscard]] Surface operator()(Curves&& cs) const;

};


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename Curvevector>
Surface Loft::execute(Curvevector&& cv) const
{
	auto tags
	{
		interface::GmshLoft {}(std::forward<Curvevector>(cv))
	};

	detail::PlaceholderSurface ps {tags[pos_]};

	// some of the curves will be part of the boundary
	for (auto& c : cv)
		ps.tryStore(c);

	return Surface {ps};
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename... Curves, typename>
Surface Loft::operator()(Curves&&... cs) const
{
	auto&& makeSptr = [](auto&& c)
	{
		using Type = decltype(c);

		if constexpr (isSptr_v<Type>)
		{
			return c;
		}
		else
			return Sptr<Curve>
			{
				new removeCVRef_t<Type> {std::forward<Type>(c)}
			};
	};

	Sptrvector<Curve> tmp {};
	tmp.reserve(sizeof...(cs));

	(
		tmp.emplace_back
		(
			makeSptr(std::forward<Curves>(cs))
		),
		...
	);

	return execute(std::move(tmp));
}


template<typename Curves, typename>
Surface Loft::operator()(Curves&& cs) const
{
	return execute(std::forward<Curves>(cs));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace operators
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
