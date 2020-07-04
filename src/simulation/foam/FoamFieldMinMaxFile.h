/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/turbo_post/fieldMinMax file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_FIELD_MIN_MAX_FILE_H
#define SIMULATION_FOAM_FOAM_FIELD_MIN_MAX_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamFieldMinMaxFile
{
R"(
turbo_fieldMinMax_p
{
    type            fieldMinMax;
    libs            ( "libfieldFunctionObjects.so" );
    writeControl    onEnd;
    log             false;
    write           true;
    location        true;
    mode            magnitude;
    fields          ( p );
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
