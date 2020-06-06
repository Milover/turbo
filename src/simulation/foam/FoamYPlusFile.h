/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/turbo_post/yPlus file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_Y_PLUS_FILE_H
#define SIMULATION_FOAM_FOAM_Y_PLUS_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamYPlusFile
{
R"(
turbo_yPlus
{
    type            yPlus;
    libs            ( "libfieldFunctionObjects.so" );
    writeControl    onEnd;
    log             false;
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
