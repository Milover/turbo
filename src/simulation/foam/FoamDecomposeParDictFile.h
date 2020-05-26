/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/decomposeParDict file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_DECOMPOSE_PAR_DICT_FILE_H
#define SIMULATION_FOAM_FOAM_DECOMPOSE_PAR_DICT_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamDecomposeParDictFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      decomposeParDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

numberOfSubdomains  16;

constraints
{
    processors
    {
        type        singleProcessorFaceSets;
        sets        ((f0 -1));
    }
}

method              scotch;


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
