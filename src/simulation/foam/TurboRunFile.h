/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	turbo_run file contents

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_TURBO_RUN_FILE_H
#define SIMULATION_FOAM_TURBO_RUN_FILE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const String turboRunFile
{
R"(#!/bin/sh

# Run from this directory
cd ${0%/*} || exit 1

. $WM_PROJECT_DIR/bin/tools/RunFunctions

# get app and nproc
application=$(getApplication)

# exit on error
set -e

# reset
cp -r 0.orig 0

# create mesh
runApplication gmshToFoam ./*msh > log.turbo

# create patches
runApplication createPatch -overwrite >> log.turbo

# create sets
runApplication setSet -latestTime -noVTK -batch ./system/setSet.batch >> log.turbo

# prep mesh
runApplication decomposePar -force -latestTime >> log.turbo
runParallel renumberMesh -overwrite -latestTime >> log.turbo
runParallel checkMesh -latestTime -allTopology -allGeometry >> log.turbo

touch case.foam

# initialize
runParallel potentialFoam >> log.turbo

# run
runParallel $application >> log.turbo

# reconstruct
runApplication reconstructPar -latestTime >> log.turbo
)"
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
