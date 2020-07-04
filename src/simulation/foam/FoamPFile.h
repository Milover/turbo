/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	0.orig/p file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_P_FILE_H
#define SIMULATION_FOAM_FOAM_P_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String foamPFile
{
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       volScalarField;
    location    "0";
    object      p;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include		"../turbo_values";

dimensions      [0 2 -2 0 0 0 0];

internalField   uniform $KinematicPressureDifference;

boundaryField
{
    inlet
    {
        type            zeroGradient;
    }

    outlet
    {
        type            zeroGradient;
//        type            fixedValue;
//        value           $internalField;
    }

    ".*wall.*"
    {
        type            zeroGradient;
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
