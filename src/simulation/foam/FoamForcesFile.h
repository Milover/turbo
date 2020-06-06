/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/turbo_post/forces file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_FORCES_FILE_H
#define SIMULATION_FOAM_FOAM_FORCES_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamForcesFile
{
R"(
turbo_forces
{
    type            forces;
    libs            ( "libforces.so" );
    writeControl    onEnd;
    log             false;
    p               p;
    U               U;
    rho             rhoInf;
    rhoInf          $Density;
    CofR            ( 0 0 0 );
    patches         ( wall_top wall_bot wall_te );
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
