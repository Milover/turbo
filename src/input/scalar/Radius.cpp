/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Radius.h"

#include "General.h"
#include "HubRadius.h"
#include "InitialDesign.h"
#include "NumberOfStations.h"
#include "ShroudRadius.h"
#include "TipClearance.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Radius::Radius(const Float f)
:
	PVBase {f}
{}


Radius::Radius
(
	const Integer i_s,				// station number (0, 1, 2...)
	const NumberOfStations& N_s,
	const HubRadius& r_h,
	const ShroudRadius& r_s,
	const TipClearance& z_tip
)
:
	Radius
	{
		compute::computeStationRadius
		(
			i_s,
			N_s.value(),
			r_h.value(),
			r_s.value(),
			z_tip.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
