/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "BLFirstCellHeight.h"

#include "BladeVelocity.h"
#include "Chord.h"
#include "ComputeGeneral.h"
#include "Density.h"
#include "DynamicViscosity.h"
#include "General.h"
#include "InletVelocity.h"
#include "YPlus.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BLFirstCellHeight::BLFirstCellHeight(const Float f)
:
	PVBase {f}
{}


BLFirstCellHeight::BLFirstCellHeight
(
	const InletVelocity& c_1,
	const BladeVelocity& U,
	const Chord& c,
	const DynamicViscosity& mu,
	const Density& rho,
	const YPlus& y_plus
)
:
	BLFirstCellHeight
	{
		compute::computeBLFirstCellHeight
		(
			c_1.value() - U.value(),	// relative velocity
			c.value(),
			mu.value(),
			rho.value(),
			y_plus.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
