/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "gmsh.h"

#include "Curve.h"
#include "Line.h"
#include "Point.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Integer Line::construct
(
	const Integer startTag,
	const Integer endTag
) const noexcept
{
	return gmsh::model::occ::addLine
	(
		startTag,
		endTag
	);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Line::Line
(
	Point start,
	Point end
) noexcept
:
	Curve
	{
		construct
		(
			start.getDimTag().second,
			end.getDimTag().second
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
