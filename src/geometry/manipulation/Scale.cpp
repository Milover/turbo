/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <stdexcept>

#include "gmsh.h"

#include "Translate.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Translate::Translate(const Vector& vector)
:
	parameter_ {std::make_unique<Vector>(vector)}
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

Translate::~Translate()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Translate::manipulate
(
	const Vectorpair<int>& dimTags
) const
{
	if (!parameter_)
		throw std::runtime_error
		(
			"turbo::geometry::Translate::"
			"manipulate(const turbo::Vectorpair&): "
			"Manipulation parameter unset"
		);

	gmsh::model::geo::translate
	(
		dimTags,
		parameter_->x,
		parameter_->y,
		parameter_->z
	);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
