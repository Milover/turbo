/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cassert>

#include "Bezier.h"

#include "GmshBezier.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Bezier::construct(const Pointvector& points) const noexcept
{
	auto returnTag
	{
		interface::GmshBezier {}
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

Bezier::Bezier(const Coordvector& coords)
:
	Bezier
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
