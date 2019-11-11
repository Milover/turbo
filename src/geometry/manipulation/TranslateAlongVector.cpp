/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TranslateAlongVector.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

TranslateAlongVector::~TranslateAlongVector()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void TranslateAlongVector::setParameters(const Vector& vector) noexcept
{
	setVector(vector);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
