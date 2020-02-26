/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Wire

Description
	Wire class.

	XXX:
		Do not use to construct other curves/loops!
		Do not manipulate in any way!
		Use only to create surfaces (and consume in the process)!
		Make sure to use before it goes out of scope because it doesn't
		own any actual geometry!

	TODO:
		Think about removing completely (wrap in surface construction).

\*---------------------------------------------------------------------------*/

#ifndef WIRE_H
#define WIRE_H

#include <type_traits>
#include <utility>
#include <vector>

#include "gmsh.h"

#include "Shape.h"
#include "Curve.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
							Class Wire Definition
\*---------------------------------------------------------------------------*/

class Wire final
:
	public Shape
{
private:

	// Member functions

		//- Construct spline geometry
		template<typename... T>
		std::enable_if_t<std::conjunction_v<std::is_base_of<Curve, T>...>, int>
		construct(const T&... t) const noexcept
		{
			std::vector<int> tags
			{
				t.getDimTag().second...
			};
			
			return gmsh::model::occ::addWire(tags);
		}


public:

	// Constructors

		//- Construct from curves
		//  (we take a copy to avoid dependency issues)
		template<typename... T>
		Wire(const T... t) noexcept
		:
			Shape
			{
				std::pair<int, int>
				{
					1,		// dimension
					construct(t...)
				}
			}
		{
			// we cannot call the destructor regularly because gmsh's
			// implementation of wires/loops is very odd
			release();
		}

		//- Disallow copy construction
		Wire(const Wire&) = delete;

		//- Move constructor
		Wire(Wire&& loop) noexcept
		:
			Shape
			{
				std::move(loop)
			}
		{
			release();
		}


	//- Destructor
	~Wire() = default;


	// Member operators

		//- Disallow assignment
		Wire& operator=(const Wire&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
