/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::detail::PlaceholderPoint

Description
	PlaceholderPoint class

SourceFiles
	PlaceholderPoint.cpp

\*---------------------------------------------------------------------------*/

#ifndef GEOMETRY_DETAIL_PLACEHOLDER_POINT_H
#define GEOMETRY_DETAIL_PLACEHOLDER_POINT_H

#include "Error.h"
#include "PlaceholderShape.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

/*---------------------------------------------------------------------------*\
						Class PlaceholderPoint Declaration
\*---------------------------------------------------------------------------*/

class PlaceholderPoint final
:
	public PlaceholderShape
{
private:

	// Private Data

		Vector coordinates_;


public:

	// Constructors

		//- Construct from a tag and get the coordinates
		explicit PlaceholderPoint(const std::size_t t) noexcept(ndebug);


	// Member functions

		//- Get the coordinates
		Vector coordinates() const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
