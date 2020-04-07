/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <optional>
#include <stdexcept>

#include "gmsh.h"

#include "Axis.h"
#include "Error.h"
#include "Rotate.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * * //

void Rotate::executeManipulation
(
	const Vectorpair<int>& dimTags
) const
{
	if (!isSet())
		THROW_RUNTIME_ERROR("rotation parameters not set");

	PointCoordinates p {axis_->getPointCoordinates()};
	Vector v {axis_->getVector()};

	gmsh::model::occ::rotate
	(
		dimTags,
		p.at(Axis::X),
		p.at(Axis::Y),
		p.at(Axis::Z),
		v.x,
		v.y,
		v.z,
		angle_
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Rotate::setParameters
(
	const double& angle,
	const std::optional<Axis>& axis
) noexcept
{
	angle_ = angle;
	
	if
	(
		axis == std::nullopt &&
		!isSet()
	)
		axis_.reset
		(
			new Axis {ZAxis {}}
		);
	else if (axis != std::nullopt)
		axis_.reset
		(
			new Axis {axis.value()}
		);
}


bool Rotate::isSet() const noexcept
{
	return static_cast<bool>(axis_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
