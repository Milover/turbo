/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <stdexcept>

#include "gmsh.h"

#include "Axis.h"
#include "Point.h"
#include "Scale.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * * //

void Scale::executeManipulation
(
	const Vectorpair<int>& dimTags
) const
{
	if (!isSet())
		throw std::runtime_error
		(
			"turbo::geometry::Scale::"
			"manipulate(const turbo::Vectorpair<int>&): "
			"Scale factors unset"
		);

	gmsh::model::geo::dilate
	(
		dimTags,
		point_->at(Axis::X),
		point_->at(Axis::Y),
		point_->at(Axis::Z),
		scaleFactors_->at(Axis::X),
		scaleFactors_->at(Axis::Y),
		scaleFactors_->at(Axis::Z)
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Scale::setParameters
(
	const Point& point,
	const double& fx,
	const double& fy,
	const double& fz
) noexcept
{
	point_.reset
	(
		new PointCoordinates {point.getCoordinates()}
	);

	scaleFactors_.reset
	(
		new PointCoordinates {fx, fy, fz}
	);
}


void Scale::setParameters
(
	const Point& point,
	const double factor
) noexcept
{
	setParameters(point, factor, factor);
}


void Scale::setParameters(const double factor) noexcept
{
	setParameters
	(
		Point {0.0, 0.0},
		factor
	);
}


bool Scale::isSet() const noexcept
{
	return static_cast<bool>(point_)
		&& static_cast<bool>(scaleFactors_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
