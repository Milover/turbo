/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/turbo_post/patchSurfaceFieldValue file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_PATCH_SURFACE_FIELD_VALUE_H
#define SIMULATION_FOAM_FOAM_PATCH_SURFACE_FIELD_VALUE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamPatchSurfaceFieldValueFile
{
R"(
__patchSurfaceFieldValue
{
        type            surfaceFieldValue;
        libs            ( "libfieldFunctionObjects.so" );
        writeControl    onEnd;
        log             false;
        writeFields     true;
        surfaceFormat   none;

        regionType      patch;
        operation       areaAverage;

        fields          ( p U );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

turbo_patchSurfaceFieldValue_inlet
{
        ${__patchSurfaceFieldValue}

        name            inlet;
}


turbo_patchSurfaceFieldValue_outlet
{
        ${__patchSurfaceFieldValue}

        name            outlet;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#remove "__.*"

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
