/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Declarations of equations used during the initial design phase.

	NOTE:
		- all expressions assume a 2D flow
		- all expressions assume rotation around the y-axis
		- floating point exceptions are not handled/checked

\*---------------------------------------------------------------------------*/

#ifndef COMPUTE_INITIAL_DESIGN_H
#define COMPUTE_INITIAL_DESIGN_H

#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Compute blade velocity
Vector computeBladeVelocity
(
	const Float N,			// rev. per second
	const Float r			// radius
);


//- Compute relative fluid inlet/outlet angle in radians.
Float computeFluidAngle
(
	const Vector& c,		// abs. fluid inlet/outlet velocity
	const Vector& U			// blade velocity
);


//- Apply deHaller criterion to an abs. outlet velocity vector i.e.
//  construct a new outlet velocity vector such that the deHaller criterion
//  is satisfied.
Vector deHaller
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U			// blade velocity
);


//- Compute the velocity at the root of the blade.
Vector computeRootVelocity
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float dp,		// total pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float rho		// density
);


//- Compute a velocity at the specified radius
//  based on the prescribed vortex distribution.
Vector computeVortexDistributionVelocity
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float n,			// vortex distribution exponent
	const Float r,			// radius
	const Float r_h		// hub radius
);


//- Compute the camber angle
Float computeCamberAngle
(
	const Vector& c_1,			// abs. fluid inlet velocity
	const Vector& c_2,			// abs. fluid outlet velocity
	const Vector& U,  			// blade velocity
	const Float i = 0.0,		// incidence angle
	const Float delta = 0.0	// deviation angle
);


//- Compute total pressure difference
Float computeTotalPressureDifference
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float rho		// density
);


//- Compute chord at specified radius
Float computeChord
(
	const Integer N_b,		// number of blades
	const Float r,			// radius
	const Float sigma		// solidity
);


//- Compute chord at specified radius
Float computeStaggerAngle
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& U,  		// blade velocity
	const Float zeta,		// leading edge inclination
	const Float i = 0.0	// incidence angle
);


//- Compute inlet velocity
//  NOTE: no pre-swirl is assumed
Float computeInletVelocity
(
	const Float Q,			// volume flow rate
	const Float r_h,		// hub radius
	const Float r_s		// shroud radius
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
