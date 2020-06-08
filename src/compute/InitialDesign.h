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

//- Compute the max (rel) profile thickness such that
//	the requested max abs. blade thickness is satisfied
//	NOTE: we assume a symmetric thickness distribution
[[deprecated("we're not using this anymore")]]
Float computeBladeThicknessForcedMaxProfileThickness
(
	const Float c,			// chord
	const Float r,			// (profile section) radius
	const Float t_abs		// max abs. blade thickness
) noexcept;


//- Compute the chord for a given axial chord and stagger angle,
//	returns min[chord, chord_lim]
[[deprecated("we're not using this anymore")]]
Float computeAxialLimitedChord
(
	const Float c,			// chord
	const Float b,			// axial chord (passage width)
	const Float xi			// stagger angle
) noexcept;


//- Compute blade velocity
Vector computeBladeVelocity
(
	const Float N,			// rev. per second
	const Float r			// radius
) noexcept;


//- Compute the camber angle
Float computeCamberAngle
(
	const Vector& c_1,			// abs. fluid inlet velocity
	const Vector& c_2,			// abs. fluid outlet velocity
	const Vector& U,  			// blade velocity
	const Float i = 0.0,		// incidence angle
	const Float delta = 0.0		// deviation angle
) noexcept;


//- Compute chord from pitch and solidity
Float computeChord
(
	const Float l,			// pitch
	const Float sigma		// solidity
) noexcept;


//- Compute chord at specified radius
Float computeChord
(
	const Integer N_b,		// number of blades
	const Float r,			// radius
	const Float sigma		// solidity
) noexcept;


//- Compute relative fluid inlet/outlet angle in radians.
Float computeFluidAngle
(
	const Vector& c,		// abs. fluid inlet/outlet velocity
	const Vector& U			// blade velocity
) noexcept;


//- Compute inlet velocity
//  NOTE: no pre-swirl is assumed
Vector computeInletVelocity
(
	const Float Q,			// volume flow rate
	const Float r_h,		// hub radius
	const Float r_s			// shroud radius
) noexcept;


//- Compute pitch at a given radius
Float computePitch
(
	const Integer N_b,		// number of blades
	const Float r			// radius
) noexcept;


//- Compute blade span
Float computeSpan
(
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float z_tip = 0.0	// tip gap (clearance)
) noexcept;


//- Compute chord at specified radius
Float computeStaggerAngle
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& U,  		// blade velocity
	const Float zeta,		// leading edge inclination
	const Float i = 0.0		// incidence angle
) noexcept;


//- Compute radius for an airfoil station
Float computeStationRadius 
(
	const Integer i_s,		// station number (0, 1, 2...)
	const Integer N_s,		// number of stations
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float z_tip = 0	// tip gap (clearance)
) noexcept;


//- Compute total pressure difference
Float computeStaticPressureDifference
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float rho			// density
) noexcept;


//- Compute the swirl constant at hub such that the pressure rise is maximal
Vector computeRootOutletVelocity
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float N,			// rev. per second
	const Float r_h			// hub radius
) noexcept;


//- Compute the swirl constant at hub,
//	simply computes the swirl for the maximum pressure difference possible
[[deprecated("not using this anymore")]]
Vector computeRootOutletVelocity_depr
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float dp,			// (requested total) static pressure difference
	const Float eta,		// total to total efficiency
	const Float N,			// rev. per second
	const Float n,			// vortex distribution coefficient
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float rho			// density
) noexcept;


//- Compute the vortex distribution exponent, such that
//	the cyl. section integral work is equal to the requested work
Float computeVortexDistributionExponent
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float dp,			// (requested total) static pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float rho			// density
) noexcept;


//- Compute a velocity at the specified radius
//  based on the prescribed vortex distribution.
Vector computeVortexDistributionVelocity
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float n,			// vortex distribution exponent
	const Float r,			// radius
	const Float r_h			// hub radius
) noexcept;


//- Apply deHaller criterion to an abs. outlet velocity vector i.e.
//  construct a new outlet velocity vector such that the deHaller criterion
//  is satisfied.
Vector deHaller
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Float N,			// rev. per second
	const Float r_h			// hub radius
) noexcept;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
