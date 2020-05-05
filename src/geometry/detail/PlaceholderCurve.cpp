/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "PlaceholderCurve.h"

#include "Error.h"
#include "Entity.h"
#include "General.h"
#include "GmshBoundary.h"
#include "PlaceholderPoint.h"
#include "PlaceholderShape.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

PlaceholderCurve::PlaceholderCurve(const std::size_t t) noexcept(ndebug)
:
	PlaceholderShape {t}
{
	auto points
	{
		interface::GmshBoundary {}(tag, Entity1D::dim)
	};

	boundary_.reserve(points.size());
	for (auto p : points)
		boundary_.emplace_back(p, nullptr);
}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Vectorpair<PlaceholderPoint, Sptr<Point>>
PlaceholderCurve::boundary() const noexcept
{
	return boundary_;
}


void PlaceholderCurve::tryStore(const Sptr<Point>& point) noexcept
{
	for (auto& [phP, sptrP] : boundary_)
		if
		(
			!sptrP
		 && phP.tag == point->tag()
		)
			sptrP = point;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
