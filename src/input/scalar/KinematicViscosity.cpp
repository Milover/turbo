/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "KinematicViscosity.h"

#include "Density.h"
#include "DynamicViscosity.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

KinematicViscosity::KinematicViscosity(const Float f)
:
	PVBase {f}
{}


KinematicViscosity::KinematicViscosity
(
	const Density& rho,
	const DynamicViscosity& mu
)
:
	KinematicViscosity
	{
		mu.value() / rho.value()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String KinematicViscosity::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
