/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "PlaceholderPoint.h"

#include "Entity.h"
#include "Error.h"
#include "GmshBoundingBox.h"
#include "PlaceholderShape.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

PlaceholderPoint::PlaceholderPoint(const std::size_t t) noexcept(ndebug)
:
	PlaceholderShape {t}
{
	auto [min, max]		// min == max
	{
		interface::GmshBoundingBox {}(tag, Entity0D::dim)
	};

	coordinates_ = min;
}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Vector PlaceholderPoint::coordinates() const noexcept
{
	return coordinates_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
