/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "InitialDesign.h"

#include "General.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

Vector computeBladeVelocity 
(
	const Float N,			// rev. per second
	const Float r			// radius
) noexcept
{
	// we're always rotating counterclockwise
	return Vector
	{
		0.0,
		-pi * N * r
	};
}


Float computeCamberAngle 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,  		// blade velocity
	const Float i,			// incidence angle
	const Float delta		// deviation angle
) noexcept
{
	Float beta_1			// fluid inlet angle
	{
		computeFluidAngle(c_1, U)
	};
	Float beta_2			// fluid outlet angle
	{
		computeFluidAngle(c_2, U)
	};

	return i + beta_1 - (delta + beta_2);
}


Float computeChord
(
	const Float l,			// pitch
	const Float sigma		// solidity
) noexcept
{
	return sigma * l;
}


Float computeChord 
(
	const Integer N_b,		// number of blades
	const Float r,			// radius
	const Float sigma		// solidity
) noexcept
{
	Float l					// pitch
	{
		computePitch(N_b, r)
	};

	return sigma * l;
}


Float computeFluidAngle 
(
	const Vector& c,		// abs. fluid inlet/outlet velocity
	const Vector& U			// blade velocity
) noexcept
{
	Vector w {c - U};		// rel. fluid inlet/outlet velocity

	return pi - angleBetween(U, w);
}


Vector computeInletVelocity 
(
	const Float Q,			// volume flow rate
	const Float r_h,		// hub radius
	const Float r_s			// shroud radius
) noexcept
{
	Float A					// inlet cross-sectional area
	{
		pi * (std::pow(r_s, 2) - std::pow(r_h, 2))
	};

	return Vector
	{
		Q / A,
		0.0
	};
}


Float computePitch
(
	const Integer N_b,		// number of blades
	const Float r			// radius
) noexcept
{
	return 2.0 * pi * r / static_cast<Float>(N_b);
}


Vector computeRootOutletVelocity 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float dp,			// total pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float rho			// density
) noexcept
{
	Float dc_y
	{
		dp / (rho * pi * N * r_h)
	};

	return Vector
	{
		c_1.x(),
		c_1.y() + dc_y
	};
}


//- Compute blade span
Float computeSpan
(
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float z_tip		// tip gap (clearance)
) noexcept
{
	return r_s - r_h - z_tip;
}


Float computeStaggerAngle 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& U,  		// blade velocity
	const Float zeta,		// leading edge inclination
	const Float i			// incidence angle
) noexcept
{
	return i + computeFluidAngle(c_1, U) - zeta;
}


//- Compute radius for an airfoil station
Float computeStationRadius 
(
	const Integer i_s,		// station number (0, 1, 2...)
	const Integer N_s,		// number of stations
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float z_tip		// tip gap (clearance)
) noexcept
{
	Float l			// increment
	{
		computeSpan(r_h, r_s, z_tip) / static_cast<Float>(N_s + 1)
	};

	return r_h + l * static_cast<Float>(i_s + 1);
}


Float computeTotalPressureDifference 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float rho			// density
) noexcept
{
	return rho * mag(U) * (c_2.y() - c_1.y());
}


Vector computeVortexDistributionVelocity 
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float n,			// vortex distribution exponent
	const Float r,			// radius
	const Float r_h			// hub radius
) noexcept
{
	Float k
	{
		std::pow(r / r_h, n)
	};

	return Vector
	{
		c_2_h.x(),
		c_2_h.y() * k
	};
}


Vector deHaller 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U			// blade velocity
) noexcept
{
	static constexpr Float DH {0.72};	// deHaller constant

	Float a
	{
		std::pow
		(
			DH * mag(c_1 - U), 2
		)
	};
	Float b
	{
		std::pow(c_2.x(), 2)			// because U.x() == 0
	};
	Float c_2_y							// diffusion limited swirl component
	{
		U.y() + std::sqrt(a - b)		// always > 0 for compressors/fans
	};

	// if the criterion is already satissfied, return c_2
	if
	(
		isGreaterOrEqual(c_2.y(), c_2_y)
	)
		return c_2;
	// construct a compliant c_2 otherwise
	else
		return Vector
		{
			c_2.x(), c_2_y
		};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// ************************************************************************* //
