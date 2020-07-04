/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "ComputeDesign.h"

#include "General.h"
#include "InitialDesign.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

Float computeAirfoilEfficiency
(
	const Vector& c_1,			// abs. fluid inlet velocity
	const Vector& U,			// blade velocity
	const Vector& F_tot,		// total airfoil load
	const Float dp_tot,			// total pressure difference
	const Float l				// pitch
) noexcept
{
	return l * c_1.x() * dp_tot / std::abs(F_tot.y() * U.y());
}


Float computeDeviationAngle
(
	const Vector& c_2,			// abs. fluid outlet velocity (ideal)
	const Vector& U,			// blade velocity
	const Vector& w_2_real		// rel. outlet velocity (real)
) noexcept
{
	return computeFluidAngle(c_2, U) - angleBetween(w_2_real, Vector::yAxis());
}


Float computeStaggerAngleCorrection
(
	const Vector& sp,			// stagnation point
	const Vector& le,			// leading edge point
	const Vector& pc			// profile centroid
) noexcept
{
	return angleBetween(pc - sp, Vector::yAxis())
		 - angleBetween(pc - le, Vector::yAxis());
}


Float computeTotalPressureDifference 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Float dp,			// static pressure difference
	const Float rho			// density
) noexcept
{
	Float e_k
	{
		rho * 0.5 * (std::pow(mag(c_2), 2) - std::pow(mag(c_1), 2))
	};

	return dp + e_k;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// ************************************************************************* //
