/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	0.orig/omega file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_OMEGA_FILE_H
#define SIMULATION_FOAM_FOAM_OMEGA_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamOmegaFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       volScalarField;
    location    "0";
    object      omega;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include		"../turbo_values";

dimensions      [0 0 -1 0 0 0 0];

internalField   uniform $TurbulenceSpecificDissipationRate;

boundaryField
{
    inlet
    {
        type            fixedValue;
        value           $internalField;
    }

    outlet
    {
        type            freestream;
		freestreamValue	$internalField;
		value			$internalField;
    }

    ".*wall.*"
    {
        type            omegaWallFunction;
		value			$internalField;
		blended			true;
    }

    ".*periodic.*"
    {
        type            cyclicAMI;
    }

	topAndBot
	{
		type			empty;
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
