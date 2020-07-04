/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Declarations of equations used during the design phase

	NOTE:
		- all expressions assume a 2D flow
		- all expressions assume rotation around the y-axis
		- floating point exceptions are not handled/checked

\*---------------------------------------------------------------------------*/

#ifndef cOMPUTE_COMPUTE_DESIGN_H
#define COMPUTE_COMPUTE_DESIGN_H

#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Compute total-to-total efficiency of an airfoil
Float computeAirfoilEfficiency
(
	const Vector& c_1,			// abs. fluid inlet velocity
	const Vector& U,			// blade velocity
	const Vector& F_tot,		// total airfoil load
	const Float dp_tot,			// total pressure difference
	const Float l				// pitch
) noexcept;

//- Compute deviation angle from assumed and real
//	rel. outlet velocity vectors
Float computeDeviationAngle
(
	const Vector& c_2,			// abs. fluid inlet/outlet velocity (ideal)
	const Vector& U,			// blade velocity
	const Vector& w_2_real		// rel. outlet velocity (real)
) noexcept;


//- Compute stagger angle correction
Float computeStaggerAngleCorrection
(
	const Vector& sp,			// stagnation point
	const Vector& le,			// leading edge point
	const Vector& pc			// profile centroid
) noexcept;


//- Compute the (real) total pressure difference
Float computeTotalPressureDifference 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Float dp,			// static pressure difference
	const Float rho			// density
) noexcept;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
