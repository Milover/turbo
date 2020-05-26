/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	0.orig/nut file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_NUT_FILE_H
#define SIMULATION_FOAM_FOAM_NUT_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamNutFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       volScalarField;
    location    "0";
    object      nut;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include		"../turbo_values";

dimensions      [0 2 -1 0 0 0 0];

internalField   uniform $TurbulenceViscosity;

boundaryField
{
    inlet
    {
        type            calculated;
        value           $internalField;
    }

    outlet
    {
        type            calculated;
        value           $internalField;
    }

    ".*wall.*"
    {
        type            nutUBlendedWallFunction;
		value			$internalField;
    }

    ".*periodic.*"
    {
        type            cyclicAMI;
    }

    topAndBot
    {
        type            empty;
    }
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
