/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "ComputeGeneral.h"

#include "Error.h"
#include "General.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

Float computeBLFirstCellHeight
(
	const Vector& U,	// velocity
	const Float l,		// characteristic length
	const Float mu,		// dynamic viscosity
	const Float rho,	// density
	const Float y_plus	// target y+
) noexcept
{
	Float Re
	{
		reynolds(U, l, mu, rho)
	};
	Float c_f		// skin friction coeff; Schlichting, Boundary Layer Theory
	{
		std::pow(2.0 * std::log10(Re) - 0.65, -2.3)
	};
	Float tau_w		// skin friction
	{
		0.5 * rho * std::pow(mag(U), 2) * c_f
	};
	Float u_t		// friction velocity
	{
		std::sqrt(tau_w / rho)
	};

	// 2x because we want the cell height
	return 2.0 * (y_plus * mu / (u_t * rho));
}


Float computeBLThickness
(
	const Float G,		// mesh size
	const Float h_bl,	// bl first cell height
	const Float k,		// ratio, last cell height / mesh size
	const Float k_bl	// bl growth rate
) noexcept
{
	Integer n_bl		// number of boundary layer cells
	{
		static_cast<Integer>
		(
			std::round
			(
				std::log(G * k / h_bl) / std::log(k_bl)
			)
		)
	};

	return h_bl * (1.0 - std::pow(k_bl, n_bl + 1)) / (1.0 - k_bl);
}


Float computeMeshCellSize
(
	const Integer N,	// mesh size (cell count)
	const Float A		// (mesh) surface area
) noexcept
{
	// 2.0 because we're using tets exclusively
	return 2.0 * std::sqrt
	(
		A / static_cast<Float>(N)
	);
}


Vector intersectLines2D
(
	const Vector& p_1,
	const Vector& p_2,
	const Vector& q_1,
	const Vector& q_2
) noexcept(ndebug)
{
	if
	(
		!isEqual(p_1.z(), p_2.z())
	 || !isEqual(p_1.z(), q_1.z())
	 || !isEqual(p_1.z(), q_2.z())
	)
		error(FUNC_INFO, "points don't lie in a z=const. plane");

	Float delta_1		// gradient_1
	{
		(p_2.y() - p_1.y()) / (p_2.x() - p_1.x())
	};
	Float delta_2		// gradient_2
	{
		(q_2.y() - q_1.y()) / (q_2.x() - q_1.x())
	};

	Float x
	{
		(q_1.y() - p_1.y() - delta_2 * q_1.x() + delta_1 * p_1.x())
	  / (delta_1 - delta_2)
	};
	Float y
	{
		p_1.y() + delta_1 * (x - p_1.x())
	};

	return Vector {x, y, p_1.z()};
}


Float sumNTermsGeometricSeries
(
	const Float p,		// first term
	const Float r,		// ratio
	const Integer n		// number of terms
) noexcept
{
	return p * (1.0 - std::pow(r, n + 1)) / (1.0 - r);
}


Float reynolds
(
	const Vector& U,	// velocity
	const Float l,		// characteristic length
	const Float mu,		// dynamic viscosity
	const Float rho		// density
) noexcept
{
	return rho * mag(U) * l / mu;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// ************************************************************************* //
