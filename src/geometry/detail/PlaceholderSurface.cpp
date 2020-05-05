/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "PlaceholderSurface.h"

#include "Curve.h"
#include "Error.h"
#include "Entity.h"
#include "General.h"
#include "GmshBoundary.h"
#include "PlaceholderCurve.h"
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

PlaceholderSurface::PlaceholderSurface(const std::size_t t) noexcept(ndebug)
:
	PlaceholderShape {t}
{
	auto curves
	{
		interface::GmshBoundary {}(tag, Entity2D::dim)
	};

	boundary_.reserve(curves.size());
	for (auto c : curves)
		boundary_.emplace_back(c, nullptr);
}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Vectorpair<PlaceholderCurve, Sptr<Curve>>
PlaceholderSurface::boundary() const noexcept
{
	return boundary_;
}


void PlaceholderSurface::tryStore(const Sptr<Curve>& curve) noexcept
{
	for (auto& [phC, sptrC] : boundary_)
		if
		(
			!sptrC
		 && phC.tag == curve->tag()
		)
			sptrC = curve;
}


void PlaceholderSurface::tryStore(const Sptr<Point>& point) noexcept
{
	for (auto& [phC, sptrC] : boundary_)
		phC.tryStore(point);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
