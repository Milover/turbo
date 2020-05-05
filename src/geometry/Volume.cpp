/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Volume.h"

#include "General.h"
#include "PlaceholderSurface.h"
#include "Shape.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

Volume::Volume(const detail::PlaceholderVolume& v)
:
	ShapeBase {v.tag}
{
	auto surfaces {v.boundary()};

	boundary_.reserve(surfaces.size());

	for (auto& [phS, sptrS] : surfaces)
	{
		if (sptrS)
			boundary_.emplace_back(sptrS);
		else
			boundary_.emplace_back
			(
				new Surface {phS}
			);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Sptrvector<Surface>& Volume::boundaryRef() noexcept
{
	return boundary_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
