/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Declarations of general arithmetic equations.

	NOTE:
		- floating point exceptions are not handled/checked

\*---------------------------------------------------------------------------*/

#ifndef COMPUTE_GENERAL_H
#define COMPUTE_GENERAL_H

#include "Error.h"
#include "General.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace compute
{

// * * * * * * * * * * * * * * Functions * * * * * * * * * * * * * * * * * * //

//- Compute the boundary layer (first) cell height
Float computeBLFirstCellHeight
(
	const Vector& U,	// velocity
	const Float l,		// characteristic length
	const Float mu,		// dynamic viscosity
	const Float rho,	// density
	const Float y_plus	// target y+
) noexcept;


//- Compute total boundary layer thickness
Float computeBLThickness
(
	const Float G,		// avg. (mesh) cell size
	const Float h_bl,	// first cell height
	const Float k,		// last cell height / mesh size
	const Float k_bl	// bl growth rate
) noexcept;


//- Compute avg. (tet) mesh cell size
//	FIXME: this works horribly
Float computeMeshCellSize
(
	const Integer N,	// mesh size (cell count)
	const Float A		// (mesh) surface area
) noexcept;


//- Compute (initial) inlet turbulence kinetic energy
Float computeTurbulenceKineticEnergy
(
	const Vector& v,	// (inlet) velocity
	const Float I		// turbulence intensity
) noexcept;


//- Compute (initial) inlet turbulence dissipation rate
Float computeTurbulenceDissipationRate
(
	const Float k,		// turbulence kinetic energy
	const Float L		// turbulence reference length scale
) noexcept;


//- Compute (initial) inlet turbulence specific dissipation rate
Float computeTurbulenceSpecificDissipationRate
(
	const Float k,		// turbulence kinetic energy
	const Float L		// turbulence reference length scale
) noexcept;


//- Compute initial turbulence viscosity, just an approximation
Float computeTurbulenceViscosity
(
	const Float k,		// turbulence kinetic energy
	const Float L		// turbulence reference length scale
) noexcept;


//- Compute (2d) intersection between two lines,
//	all points must lie in a z=const. plane
Vector intersectLines2D
(
	const Vector& p_1,
	const Vector& p_2,
	const Vector& q_1,
	const Vector& q_2
) noexcept(ndebug);


//- Sum of geometric series
Float sumNTermsGeometricSeries
(
	const Float p,		// first term
	const Float r,		// ratio
	const Integer n		// number of terms
) noexcept;


//- Compute Reynolds number
Float reynolds
(
	const Vector& U,	// velocity
	const Float l,		// characteristic length
	const Float mu,		// dynamic viscosity
	const Float rho		// density
) noexcept;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace compute
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
