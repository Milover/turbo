/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "InletRefPoint.h"

#include "Chord.h"
#include "Error.h"
#include "RelMeshSize.h"
#include "SectionExtensionFactor.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

InletRefPoint::InletRefPoint(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


InletRefPoint::InletRefPoint
(
	const Chord& c,
	const RelMeshSize& rms,
	const SectionExtensionFactor& sef,
	const Vector& lePoint
) noexcept(ndebug)
:
	InletRefPoint
	{
		lePoint - Vector::xAxis() * c.value() * (sef.value() - rms.value())
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String InletRefPoint::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
