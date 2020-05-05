/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "Pitch.h"

#include "General.h"
#include "InitialDesign.h"
#include "NumberOfBlades.h"
#include "Radius.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Pitch::Pitch(const Float f)
:
	PVBase {f}
{}


Pitch::Pitch
(
	const NumberOfBlades& N_b,
	const Radius& r
)
:
	Pitch
	{
		compute::computePitch
		(
			N_b.value(),
			r.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
