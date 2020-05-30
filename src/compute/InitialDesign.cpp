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
	Float beta_1			// rel. fluid inlet angle
	{
		computeFluidAngle(c_1, U)
	};
	Float beta_2			// rel. fluid outlet angle
	{
		computeFluidAngle(c_2, U)
	};

	return delta + beta_2 - (i + beta_1);
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
	const Float dp,			// static pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float rho			// density
) noexcept
{
	Vector U
	{
		computeBladeVelocity(N, r_h)
	};
	Float D
	{
		std::pow(mag(U), 2) - 2.0 * dp / rho
	};

	Float c_y;
	if (isLessOrEqual(D, 0.0))
		c_y = U.y();
	else
		c_y = U.y() - std::sqrt(D);		// because U.y() always < 0, see note
										// on blade velocity

	return Vector {c_1.x(), c_y};
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
	return 0.5 * pi - i - computeFluidAngle(c_1, U) - zeta;
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
	if (N_s == 1)
		return 0.5 * (r_h + r_s);

	Float l			// increment
	{
		computeSpan(r_h, r_s, z_tip) / static_cast<Float>(N_s - 1)
	};

	return r_h + l * static_cast<Float>(i_s);
}


Float computeStaticPressureDifference 
(
	const Vector& c_1,		// abs. fluid inlet velocity
	const Vector& c_2,		// abs. fluid outlet velocity
	const Vector& U,		// blade velocity
	const Float rho			// density
) noexcept
{
	Float e_k
	{
		0.5 * (std::pow(mag(c_2), 2) - std::pow(mag(c_1), 2))
	};

	return rho * (U.y() * c_2.y() - e_k);
}


Float computeVortexDistributionExponent
(
	const Vector& c_2_h,	// abs. root (hub) fluid outlet velocity
	const Float dp,			// (requested total) static pressure difference
	const Float N,			// rev. per second
	const Float r_h,		// hub radius
	const Float r_s,		// shroud radius
	const Float rho			// density
) noexcept
{
	Float D {r_s / r_h};
	Float K_1	// we didn't keep track while deriving => |c_2_h.y()|
	{
		2.0 * N * pi * std::abs(c_2_h.y()) * std::pow(r_h, 2)
	};
	Float K_2
	{
		-0.5 * std::pow(c_2_h.y(), 2) * (std::pow(D, 2) - 1.0)
	};
	Float K_3
	{
		-dp * (std::pow(D, 2) - 1.0) / rho
	};

	auto f = [&](auto&& n)
	{
		auto a {n + 3.0};
		auto b {2.0 * n};

		return K_1 * (std::pow(D, a) - 1.0) / a
			 + K_2 * std::pow(0.5 * (D - 1.0), b)
			 + K_3;
	};
	auto dfdn = [&](auto&& n)
	{
		auto a {n + 3.0};
		auto b {2.0 * n};

		return K_1
			 * (std::pow(D, a) * (a * std::log(D) - 1.0) + 1.0)
			 / std::pow(a, 2)
			 + K_2
			 * std::pow(2.0, 1.0 - b)
			 * std::pow(D - 1.0, b)
			 * std::log(0.5 * (D - 1.0));
	};

	auto n (math::NewtonRaphson {}(0.0, f, dfdn));

	// limited to [-1, 1]
	if (n > 1.0)
	{
		if constexpr (ndebug)
		{
			std::cerr << "WARNING: "
						 "vortex distribution exponent limited to 1.0\n"
						 "computed value: "
					  << n << '\n';
		}
		n = 1.0;
	}
	else if (n < -1.0 || std::isnan(n))	// nan for n = -3
	{
		if constexpr (ndebug)
		{
			std::cerr << "WARNING: "
						 "vortex distribution exponent limited to -1.0\n"
						 "computed value: "
					  << n << '\n';
		}
		n = -1.0;
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
