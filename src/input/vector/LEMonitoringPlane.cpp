/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "LEMonitoringPlane.h"

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

LEMonitoringPlane::LEMonitoringPlane(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


LEMonitoringPlane::LEMonitoringPlane
(
	const Vector& lePoint,
	const Chord& c,
	const MonitoringPlaneOffset& mpo
) noexcept(ndebug)
:
	LEMonitoringPlane
	{
		lePoint - c.value() * mpo.value() * Vector::xAxis()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String LEMonitoringPlane::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
