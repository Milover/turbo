/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "Spline.h"

#include "GmshSpline.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Spline::construct(const Pointvector& points) const noexcept
{
	auto returnTag
	{
		interface::GmshSpline {}
		(
			tag_,
			startRef(),
			points,
			endRef()
		)
	};

	assert(returnTag == tag_);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Spline::Spline(const Coordvector& coords)
:
	Spline
	{
		coords.front(),
		coords,
		coords.back()
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
