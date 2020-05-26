/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/createPatchDict file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_CREATE_PATCH_DICT_FILE_H
#define SIMULATION_FOAM_FOAM_CREATE_PATCH_DICT_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamCreatePatchDictFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      createPatchDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include                        "../turbo_values"

pointSync                       false;

patches
(
    {
        name                    periodic_top;
        patchInfo
        {
            type                cyclicAMI;
            neighbourPatch      periodic_bot;
            transform           translational;
            separationVector    $TranslationPerTop;
        }
        constructFrom           patches;
        patches                 (per_top);
    }
 
    {
        name                    periodic_bot;
        patchInfo
        {
            type                cyclicAMI;
            neighbourPatch      periodic_top;
            transform           translational;
            separationVector    $TranslationPerTop;
        }
        constructFrom           patches;
        patches                 (per_bot);
    }

    {
        name                    wall_top;
        patchInfo
        {
            type                wall;
        }
        constructFrom           patches;
        patches                 (profile_top);
    }

    {
        name                    wall_bot;
        patchInfo
        {
            type                wall;
        }
        constructFrom           patches;
        patches                 (profile_bot);
    }

    {
        name                    wall_te;
        patchInfo
        {
            type                wall;
        }
        constructFrom           patches;
        patches                 (profile_te);
    }

    {
        name                    topAndBot;
        patchInfo
        {
            type                empty;
        }
        constructFrom           patches;
        patches                 (empty);
    }
);


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
