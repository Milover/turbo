/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "KinematicPressureDifference.h"

#include "Density.h"
#include "General.h"
#include "StaticPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

KinematicPressureDifference::KinematicPressureDifference(const Float f)
:
	PVBase {f}
{}


KinematicPressureDifference::KinematicPressureDifference
(
	const StaticPressureDifference& dp,
	const Density& rho
)
:
	KinematicPressureDifference
	{
		dp.value() / rho.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String KinematicPressureDifference::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
