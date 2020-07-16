/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/fvSchemes file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_FV_SCHEMES_FILE_H
#define SIMULATION_FOAM_FOAM_FV_SCHEMES_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamFvSchemesFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      fvSchemes;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

ddtSchemes
{
    default         steadyState;
}

gradSchemes
{
    default         cellLimited Gauss linear 1;
}

divSchemes
{
    default         none;

    div(phi,U)      bounded Gauss linearUpwindV grad(U);
    div(div(phi,U)) Gauss linear;

    div(phi,k)      bounded Gauss upwind;
    div(phi,omega)  bounded Gauss upwind;

    div((nuEff*dev2(T(grad(U))))) Gauss linear;
}

laplacianSchemes
{
    default         Gauss linear limited 0.5;
}

interpolationSchemes
{
    default         linear;
}

snGradSchemes
{
    default         limited 0.5;
}

wallDist
{
    method          meshWave;
}


// ************************************************************************* //
)"
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
