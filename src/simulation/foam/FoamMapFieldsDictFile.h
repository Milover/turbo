/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	system/mapFieldsDict file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_MAP_FIELDS_DICT_FILE_H
#define SIMULATION_FOAM_FOAM_MAP_FIELDS_DICT_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamMapFieldsDictFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "system";
    object      mapFieldsDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

patchMap
();

cuttingPatches
(
    inlet
	outlet
	periodic_top
	periodic_bot
	wall_top
	wall_bot
	wall_te
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
