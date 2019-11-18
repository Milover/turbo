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
#include "Translate.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * * //

void Translate::executeManipulation(const Vectorpair<int>& dimTags) const
{
	if (!isSet())
		throw std::runtime_error
		(
			"turbo::geometry::Translate::"
			"manipulate(const turbo::Vectorpair<int>&): "
			"Translation vector unset"
		);

	gmsh::model::geo::translate
	(
		dimTags,
		vector_->x,
		vector_->y,
		vector_->z
	);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Translate::setParameters(const Vector& vector) noexcept
{
	vector_.reset
	(
		new Vector {vector}
	);
}


void Translate::setParameters
(
	const Point& pFrom,
	const Point& pTo
) noexcept
{
	PointCoordinates p1 {pFrom.getCoordinates()};
	PointCoordinates p2 {pTo.getCoordinates()};

	Vector vector
	{
		p2[Axis::X] - p1[Axis::X],
		p2[Axis::Y] - p1[Axis::Y],
		p2[Axis::Z] - p1[Axis::Z]
	};

	setParameters(vector);
}


bool Translate::isSet() const noexcept
{
	return static_cast<bool>(vector_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
