/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "Axis.h"
#include "Point.h"
#include "TranslateToPoint.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

TranslateToPoint::~TranslateToPoint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void TranslateToPoint::setParameters
(
	const Point& fromPoint,
	const Point& toPoint
) noexcept
{
	std::vector<double> from {fromPoint.getCoordinates()};
	std::vector<double> to {toPoint.getCoordinates()};

	Vector vector
	{
		to[toUnderlying(Axis::X)] - from[toUnderlying(Axis::X)],
		to[toUnderlying(Axis::Y)] - from[toUnderlying(Axis::Y)],
		to[toUnderlying(Axis::Z)] - from[toUnderlying(Axis::Z)]
	};

	setVector(vector);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
