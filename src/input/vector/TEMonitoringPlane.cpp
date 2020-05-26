/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TEMonitoringPlane.h"

#include "Chord.h"
#include "Error.h"
#include "MonitoringPlaneOffset.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TEMonitoringPlane::TEMonitoringPlane(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


TEMonitoringPlane::TEMonitoringPlane
(
	const Vector& tePoint,
	const Chord& c,
	const MonitoringPlaneOffset& mpo
) noexcept(ndebug)
:
	TEMonitoringPlane
	{
		tePoint + c.value() * mpo.value() * Vector::xAxis()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TEMonitoringPlane::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
