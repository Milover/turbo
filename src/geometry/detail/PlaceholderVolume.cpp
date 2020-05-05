/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "PlaceholderVolume.h"

#include "Curve.h"
#include "Error.h"
#include "Entity.h"
#include "General.h"
#include "GmshBoundary.h"
#include "PlaceholderShape.h"
#include "PlaceholderSurface.h"
#include "Point.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{
namespace detail
{

// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

PlaceholderVolume::PlaceholderVolume(const std::size_t t) noexcept(ndebug)
:
	PlaceholderShape {t}
{
	auto surfaces
	{
		interface::GmshBoundary {}(tag, Entity3D::dim)
	};

	boundary_.reserve(surfaces.size());
	for (auto s : surfaces)
		boundary_.emplace_back(s, nullptr);
}


// * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * //

Vectorpair<PlaceholderSurface, Sptr<Surface>>
PlaceholderVolume::boundary() const noexcept
{
	return boundary_;
}


void PlaceholderVolume::tryStore(const Sptr<Surface>& surface) noexcept
{
	for (auto& [phS, sptrS] : boundary_)
		if
		(
			!sptrS
		 && phS.tag == surface->tag()
		)
			sptrS = surface;
}


void PlaceholderVolume::tryStore(const Sptr<Curve>& curve) noexcept
{
	for (auto& [phS, sptrS] : boundary_)
		phS.tryStore(curve);
}


void PlaceholderVolume::tryStore(const Sptr<Point>& point) noexcept
{
	for (auto& [phS, sptrS] : boundary_)
		phS.tryStore(point);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace detail
} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
