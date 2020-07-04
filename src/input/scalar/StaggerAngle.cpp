/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StaggerAngle.h"

#include "ComputeDesign.h"
#include "BladeVelocity.h"
#include "General.h"
#include "InclinationAngle.h"
#include "InitialDesign.h"
#include "InletVelocity.h"
#include "Utility.h"
#include "Vector.h"

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

void StaggerAngle::correct
(
	const Vector& stagnationPt,
	const Vector& leadingEdgePt,
	const Vector& profileCentroid
)
{
	correct
	(
		compute::computeStaggerAngleCorrection
		(
			stagnationPt,
			leadingEdgePt,
			profileCentroid
		)
	);
}


String StaggerAngle::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
