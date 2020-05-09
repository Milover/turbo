/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <vector>

#include "Surface.h"

#include "Curve.h"
#include "Error.h"
#include "General.h"
#include "PlaceholderSurface.h"
#include "Point.h"
#include "Shape.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * //

Surface::Surface(const detail::PlaceholderSurface& s)
:
	ShapeBase {s.tag}
{
	auto curves {s.boundary()};

	boundary_.reserve(curves.size());

	for (auto& [phC, sptrC] : curves)
	{
		if (sptrC)
			boundary_.emplace_back(sptrC);
		else
			boundary_.emplace_back
			(
				new Curve {phC}
			);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const Sptrvector<Curve>& Surface::boundaryCRef() const noexcept
{
	return boundary_;
}


Sptrvector<Curve>& Surface::boundaryRef() noexcept
{
	return boundary_;
}


const Sptrvector<Point>& Surface::cornersCRef() const noexcept(ndebug)
{
	if (!corners_)
		error(FUNC_INFO, "corners have not been assigned");

	return *corners_;
}


Sptrvector<Point>& Surface::cornersRef() noexcept(ndebug)
{
	if (!corners_)
		error(FUNC_INFO, "corners have not been assigned");

	return *corners_;
}


const std::vector<Sptrvector<Curve>>&
Surface::holesCRef() const noexcept(ndebug)
{
	if (!holes_)
		error(FUNC_INFO, "surface doesn't have holes");

	return *holes_;
}


std::vector<Sptrvector<Curve>>& Surface::holesRef() noexcept(ndebug)
{
	if (!holes_)
		error(FUNC_INFO, "surface doesn't have holes");

	return *holes_;
}


bool Surface::hasCorners() const noexcept
{
	return static_cast<bool>(corners_);
}


bool Surface::hasHoles() const noexcept
{
	return static_cast<bool>(holes_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
