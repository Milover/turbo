/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "AirfoilEfficiency.h"

#include "AirfoilTotalForce.h"
#include "BladeVelocity.h"
#include "ComputeDesign.h"
#include "General.h"
#include "InletVelocity.h"
#include "Pitch.h"
#include "TotalPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

AirfoilEfficiency::AirfoilEfficiency(const Float f)
:
	PVBase {f}
{}


AirfoilEfficiency::AirfoilEfficiency
(
	const InletVelocity& c_1,
	const BladeVelocity& U,
	const AirfoilTotalForce& F_tot,
	const TotalPressureDifference& dp_tot,
	const Pitch& l
)
:
	AirfoilEfficiency
	{
		compute::computeAirfoilEfficiency
		(
			c_1.value(),
			U.value(),
			F_tot.value(),
			dp_tot.value(),
			l.value()
		)
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String AirfoilEfficiency::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
