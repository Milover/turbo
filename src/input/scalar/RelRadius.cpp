/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "RelRadius.h"

#include "General.h"
#include "HubRadius.h"
#include "Radius.h"
#include "ShroudRadius.h"
#include "TipClearance.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

RelRadius::RelRadius(const Float f)
:
	LVBase {f}
{}


RelRadius::RelRadius
(
	const Radius& r,
	const HubRadius& r_h,
	const ShroudRadius& r_s,
	const TipClearance& z_tip
)
:
	RelRadius
	{
		(r.value() - r_h.value())
	  / (r_s.value() - z_tip.value() - r_h.value())
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String RelRadius::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
