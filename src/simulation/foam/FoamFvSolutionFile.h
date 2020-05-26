/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/fvSolution file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_FV_SOLUTION_FILE_H
#define SIMULATION_FOAM_FOAM_FV_SOLUTION_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamFvSolutionFile
{
R"delim(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      fvSolution;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

solvers
{
    p
    {
        solver          PCG;
        preconditioner  DIC;

        minIter         3;
        tolerance       1e-7;
        relTol          0;
    }

    U
    {
        solver          PBiCGStab;
        preconditioner  DILU;

        minIter         3;
        tolerance       1e-8;
        relTol          0;
    }

    "(k|omega)"
    {
        solver          PBiCGStab;
        preconditioner  DILU;

        minIter         3;
        tolerance       1e-8;
        relTol          0;
    }

    Phi
    {
        $p;
    }
}


potentialFlow
{
    nNonOrthogonalCorrectors 30;
}


SIMPLE
{
    consistent          true;
    residualControl
    {
        p               1e-4;
        U               1e-4;
        "(k|omega)"     1e-4;
    }
}


relaxationFactors
{
    equations
    {
        U               0.85;
        "(k|omega)"     0.7;
    }
}


cache
{
    grad(U);
}


// ************************************************************************* //
)delim"
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
