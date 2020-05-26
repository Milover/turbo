/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	0.orig/U file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_U_FILE_H
#define SIMULATION_FOAM_FOAM_U_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamUFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       volVectorField;
    location    "0";
    object      U;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include 		"../turbo_values";

dimensions      [0 1 -1 0 0 0 0];

internalField   uniform $InletRelativeVelocity;

boundaryField
{
    inlet
    {
        type            fixedValue;
		value			$internalField;
    }

    outlet
    {
        type            freestreamVelocity;
		freestreamValue	uniform (0 0 0);
		value			$internalField;
    }

    ".*wall.*"
    {
        type            noSlip;
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
