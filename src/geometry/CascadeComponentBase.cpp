/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "CascadeComponentBase.h"
#include "Point.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

Vectorpair<int>  CascadeComponentBase::getDimTags() const noexcept
{

}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CascadeComponentBase::CascadeComponentBase
(
	const CascadeComponentBase& component
)
{

}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Point CascadeComponentBase::getCenter() const noexcept
{

}


Point CascadeComponentBase::translate(const Vector& vector) const noexcept
{

}


Point CascadeComponentBase::centerOnPoint(const Point& point) const noexcept
{

}


Point CascadeComponentBase::rotate(const double angle) const noexcept
{

}


Point CascadeComponentBase::scale(const double factor) const noexcept
{

}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
