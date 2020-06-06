/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/turbo_post/sampledSurfaceFieldValue file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_SAMPLED_SURFACE_FIELD_VALUE_H
#define SIMULATION_SAMPLED_SURFACE_FIELD_VALUE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamSampledSurfaceFieldValueFile
{
R"(
__surfaceFieldValue
{
        type            surfaceFieldValue;
        libs            ( "libfieldFunctionObjects.so" );
        writeControl    onEnd;
        log             false;
        writeFields     true;
        surfaceFormat   none;
        regionType      functionObjectSurface;

        fields          ( p U );
}


__areaAverage
{
        ${__surfaceFieldValue}

        operation       areaAverage;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

turbo_surfaces
{
    type                    surfaces;
    libs                    ( "libsampling.so" );
    executeControl          onEnd;
    writeControl            none;
    sampleOnExecute         true;
    store                   true;
    surfaceFormat           none;
    sampleScheme            cell;

    fields                  ( p U );

    interpolate_flag        false;
    store_flag              true;

    surfaces
    (
        turbo_le_surface
        {
            type            plane;
            source          cells;
            store           true;
            planeType       pointAndNormal;

            pointAndNormalDict
            {
                point       $LEMonitoringPlane;
                normal      (1 0 0);
            }

            interpolate     false;
        }

        turbo_te_surface
        {
            type            plane;
            source          cells;
            store           true;
            planeType       pointAndNormal;

            pointAndNormalDict
            {
                point       $TEMonitoringPlane;
                normal      (1 0 0);
            }

            interpolate     false;
        }
    );
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

turbo_areaAverage_le
{
    ${__areaAverage}

    name                    turbo_surfaces.turbo_le_surface;
}


turbo_areaAverage_te
{
    ${__areaAverage}

    name                    turbo_surfaces.turbo_te_surface;
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
