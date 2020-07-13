/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/controlDict file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_CONTROL_DICT_FILE_H
#define SIMULATION_FOAM_FOAM_CONTROL_DICT_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamControlDictFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      controlDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include          "../turbo_values"

application       simpleFoam;

startFrom         startTime;

startTime         0;

stopAt            endTime;

endTime           2000;

deltaT            1;

writeControl      timeStep;

writeInterval     500;

purgeWrite        3;

writeFormat       binary;

writePrecision    12;

writeCompression  false;

timeFormat        general;

timePrecision     8;

runTimeModifiable true;

functions
{
    #include      "turbo_post/fieldMinMax"
    #include      "turbo_post/forces"
    #include      "turbo_post/patchSurfaceFieldValue"
    #include      "turbo_post/sampledSurfaceFieldValue"
    #include      "turbo_post/yPlus"
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
