/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Volume.h"

#include "General.h"
#include "GmshVolume.h"
#include "PlaceholderSurface.h"
#include "Shape.h"
#include "Surface.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

void Volume::construct() const noexcept
{
	std::size_t returnTag;

	returnTag = interface::GmshVolume {}
	(
		tag_,
		boundaryCRef()
	);

	assert(returnTag == tag_);
}


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


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Volume::~Volume() noexcept
{
	remove();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const Sptrvector<Surface>& Volume::boundaryCRef() const noexcept
{
	return boundary_;
}


Sptrvector<Surface>& Volume::boundaryRef() noexcept
{
	return boundary_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
