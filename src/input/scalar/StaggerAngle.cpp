/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StaggerAngle.h"

#include "BladeVelocity.h"
#include "General.h"
#include "IncidenceAngle.h"
#include "InclinationAngle.h"
#include "InitialDesign.h"
#include "InletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

StaggerAngle::StaggerAngle(const Float f)
:
	RegBase {f}
{}


StaggerAngle::StaggerAngle
(
	const InletVelocity& c_1,
	const BladeVelocity& U,
	const InclinationAngle& zeta,
	const IncidenceAngle& i
)
:
	StaggerAngle
	{
		compute::computeStaggerAngle
		(
			c_1.value(),
			U.value(),
			zeta.value(),
			i.value()
		)
	}
{}


StaggerAngle::StaggerAngle
(
	const InletVelocity& c_1,
	const BladeVelocity& U,
	const InclinationAngle& zeta
)
:
	StaggerAngle
	{
		compute::computeStaggerAngle
		(
			c_1.value(),
			U.value(),
			zeta.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String StaggerAngle::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
