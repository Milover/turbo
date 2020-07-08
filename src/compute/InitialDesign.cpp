/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "InitialDesign.h"

#include "General.h"
#include "NewtonRaphson.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

Float computeAxialLimitedChord
(
	const Float c,			// chord
	const Float b,			// axial chord (passage width)
	const Float xi			// stagger angle
) noexcept
{
	Float c_lim
	{
		b / std::sin(xi)
	};

	if (isGreaterOrEqual(c, c_lim))
		return c_lim;
	else
		return c;
}


Float computeBladeThicknessForcedMaxProfileThickness
(
	const Float c,			// chord
	const Float r,			// (profile section) radius
	const Float t_abs		// max abs. blade thickness
) noexcept
{
	return 2.0 * r * std::asin(0.5 * t_abs / r) / c;
}


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
		-N * 2.0 * pi * r
	};
}


Float computeCamberAngle
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U  		// blade velocity
	//const Float i			// incidence angle
	//const Float delta		// deviation angle
	//const Float coeff		// camber angle scaling factor
) noexcept
{
	Float beta_1			// rel. fluid inlet angle
	{
		computeFluidAngle(c_1, U)
	};
	Float beta_2			// rel. fluid outlet angle
	{
		computeFluidAngle(c_2, U)
	};

	//return delta + beta_2 - (i + beta_1);
	return beta_2 - beta_1;
	//return coeff * (beta_2 - beta_1);			// XXX: testing, remove after
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
	const Float eta,		// (blade) efficiency
	const Float N,			// rev. per second
	const Float r_h			// hub radius
) noexcept
{
	Float c_2_h_y
	{
		eta * N * 2.0 * pi * r_h
	};

	return Vector {c_1.x(), -c_2_h_y};	// rotation is counterclockwise
}


[[deprecated("not using this anymore")]]
Vector computeRootOutletVelocity_depr
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Float dp,			// (requested total) static pressure difference
	const Float eta,		// (blade) efficiency
	const Float N,			// rev. per second
	const Float n,			// vortex distribution coefficient
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float rho			// density
) noexcept
{
	Float D {r_s / r_h};
	Float K_1
	{
		0.5 * std::pow(0.5 * (D - 1.0), 2.0 * n)
	};
	Float K_2
	{
		-2.0 * eta * N * 2.0 * pi * r_h * (std::pow(D, n + 3.0) - 1.0) / (n + 3.0)
	};

	// check max requested pressure
	Float dp_max
	{
		std::pow(K_2, 2) / (4.0 * rho * K_1 * (std::pow(D, 2) - 1.0))
	};

	if (!isLessOrEqual(dp, dp_max))
	{
		if constexpr (ndebug)
		{
			std::cerr << "WARNING: "
						 "recomputed static pressure difference: "
					  << dp_max << '\n';
		}
	}
	else
		dp_max = dp;

	Float K_3
	{
		(std::pow(D, 2) - 1.0) * dp_max / rho
	};

	// check discriminant
	Float discriminant
	{
		std::pow(K_2, 2) - 4.0 * K_1 * K_3
	};
	if (!isGreaterOrEqual(discriminant, 0.0))
	{
		error
		(
			FUNC_INFO,
			"discriminant < 0, try increasing the r_s/r_h ratio or the "
			"vortex distribution exponent"
		);
	}

	Float c
	{
		-K_2 + std::sqrt(discriminant) / (2.0 * K_1)
	};

	// check swirl
	Float c_max
	{
		eta * N * 2.0 * pi * r_h
	};
	if (isLessOrEqual(c_max, c))
	{
		if constexpr (ndebug)
		{
			std::cerr << "WARNING: "
						 "recomputed hub swirl component: "
					  << c_max << '\n';
		}
	}
	else
		c_max = c;


	return Vector {c_1.x(), -c_max};	// rotation is counterclockwise
}


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
	const Float zeta		// leading edge inclination
	//const Float i			// incidence angle
) noexcept
{
	//return i + computeFluidAngle(c_1, U) + zeta;
	return computeFluidAngle(c_1, U) + zeta;
}


Float computeStaticPressureDifference 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float eta,		// (blade) efficiency
	const Float rho			// density
) noexcept
{
	Float e_k
	{
		0.5 * (std::pow(mag(c_2), 2) - std::pow(mag(c_1), 2))
	};

	return rho * (eta * U.y() * c_2.y() - e_k);
}


Float computeStationRadius 
(
	const Integer i_s,		// station number (0, 1, 2...)
	const Integer N_s,		// number of stations
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float z_tip		// tip gap (clearance)
) noexcept
{
	if (N_s == 1)
		return 0.5 * (r_h + r_s);

	Float l			// increment
	{
		computeSpan(r_h, r_s, z_tip) / static_cast<Float>(N_s - 1)
	};

	return r_h + l * static_cast<Float>(i_s);
}


Float computeTargetTotalPressureDifference 
(
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float eta,		// (blade) efficiency
	const Float rho			// density
) noexcept
{
	return eta * rho * U.y() * c_2.y();
}


Float computeVortexDistributionExponent
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float dp_req,		// (requested) static pressure difference
	const Float eta,		// (blade) efficiency
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float rho			// density
) noexcept
{
	Float D {r_s / r_h};
	Float K_1
	{
		(std::pow(D, 2) - 1.0) * dp_req / rho
	};
	Float K_2
	{
		0.5 * std::pow(c_2_h.y(), 2) * (std::pow(D, 2) - 1.0)
	};
	Float K_3	// we didn't keep track of signs => |c_2_h.y()|
	{
		-2.0 * eta * N * 2.0 * pi * std::abs(c_2_h.y()) * r_h
	};

	auto f = [&](const auto& n)
	{
		auto a {n + 3.0};

		return K_1
			 + K_2 * std::pow(0.5 * (D - 1.0), 2.0 * n)
			 + K_3 * (std::pow(D, a) - 1.0) / a;
	};
	auto dfdn = [&](const auto& n)
	{
		auto a {n + 3.0};

		return K_2
			 * std::pow(2.0, 1.0 - 2.0 * n)
			 * std::pow(D - 1.0, 2.0 * n)
			 * std::log(0.5 * (D - 1.0))
			 + K_3 / std::pow(a, 2)
			 * (1.0 + std::pow(D, a) * (a * std::log(D) - 1.0));
	};
	auto n {math::NewtonRaphson {}(-1.0, f, dfdn)};

	// nan for n = -3 and must be greater than -1
	if (n < -1.0 || std::isnan(n))
		n = -1.0;

	// we have to check if the shroud swirl is physically achievable
	Float n_max
	{
		std::log(eta * N * 2.0 * pi * r_s) / std::log(std::abs(c_2_h.y()) * D)
	};
	if (!isLessOrEqual(n, n_max))
	{
		if constexpr (ndebug)
		{
			std::cerr << "WARNING: "
						 "limited vortex distribution exponent: "
					  << n_max << '\n';
		}
		n = n_max;
	}

	return n;
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
	const Float N,			// rev. per second
	const Float r_h			// hub radius
) noexcept
{
	static constexpr Float DH {0.72};	// deHaller constant

	Vector U
	{
		computeBladeVelocity(N, r_h)
	};
	Float D
	{
		std::pow(DH * mag(c_1 - U), 2) - std::pow(c_2.x(), 2)
	};

	Float c_2_y;						// diffusion limited swirl component
	if (isLessOrEqual(D, 0.0))
		c_2_y = U.y();
	else
		c_2_y = U.y() + std::sqrt(D);

	// if the criterion is already satissfied, return c_2
	if
	(
		isGreaterOrEqual(c_2.y(), c_2_y)
	)
		return c_2;
	// construct a compliant c_2 otherwise
	else
		return Vector {c_2.x(), c_2_y};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// ************************************************************************* //
