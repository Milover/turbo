/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

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
)
{
	return Vector
	{
		0.0,
		pi * N * r
	};
}


Float computeFluidAngle
(
	const Vector& c,		// abs. fluid inlet/outlet velocity
	const Vector& U			// blade velocity
)
{
	Vector w {c - U};	// rel. fluid inlet/outlet velocity

	return pi - std::acos
	(
		dot(U, w) / (mag(U) * mag(w))
	);
}


Vector deHaller
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U			// blade velocity
)
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
		isGreaterOrEqual(c2.y(), c_2_y)
	)
		return c_2;
	// construct a compliant c_2 otherwise
	else
		return Vector
		{
			c_2.x(), c_2_y
		};
}


Vector computeRootVelocity
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float dp,		// total pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float rho		// density
)
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


Vector computeVortexDistributionVelocity
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float n,			// vortex distribution exponent
	const Float r,			// radius
	const Float r_h		// hub radius
)
{
	Float k
	{
		std::pow
		(
			r / r_h, n
		)
	};

	return Vector
	{
		c_2_h.x(),
		c_2_h.y() * k
	};
}


Float computeCamberAngle
(
	const Vector& c_1,			// abs. fluid inlet velocity
	const Vector& c_2,			// abs. fluid outlet velocity
	const Vector& U,  			// blade velocity
	const Float i = 0.0,		// incidence angle
	const Float delta = 0.0	// deviation angle
)
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


Float computeTotalPressureDifference
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float rho		// density
)
{
	return rho * mag(U) * (c_2.y() - c_1.y());
}


Float computeChord
(
	const Integer N_b,		// number of blades
	const Float r,			// radius
	const Float sigma		// solidity
)
{
	Float l					// pitch
	{
		2.0 * pi * r * static_cast<Float>(N_b)
	};

	return sigma * l;
}


Float computeStaggerAngle
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& U,  		// blade velocity
	const Float zeta,		// leading edge inclination
	const Float i = 0.0	// incidence angle
)
{
	return i + computeFluidAngle(c_1, U) - zeta;
}


Float computeInletVelocity
(
	const Float Q,			// volume flow rate
	const Float r_h,		// hub radius
	const Float r_s		// shroud radius
)
{
	Float A					// inlet cross-sectional area
	{
		pi * (std::pow(r_s, 2) - std::pow(r_h, 2))
	};

	return Q / A;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
