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

# exit on error
set -e

###############################################################################

prep_mesh()
{
	runApplication decomposePar -force -latestTime >> log.turbo
	runParallel renumberMesh -overwrite -latestTime >> log.turbo
	runParallel checkMesh -latestTime -allTopology -allGeometry >> log.turbo
}

###############################################################################

# get app and nproc
application=$(getApplication)

# get previous case
prev_case_id=$(($(echo "$PWD" | sed -e 's!.*/!!' -e 's/.*\.//') - 1))
prev_case=$(echo "$PWD" | sed "s/case\..*/case.$prev_case_id/")

# reset
cp -r 0.orig 0
touch case.foam

# create mesh
runApplication gmshToFoam ./*msh > log.turbo

# create patches
runApplication createPatch -overwrite >> log.turbo

# create sets
runApplication setSet -latestTime -noVTK -batch ./system/setSet.batch >> log.turbo

# initialize
if [ -d $prev_case ]
then
	prep_mesh
	runParallel mapFieldsPar -noFunctionObjects \
							 -sourceTime 'latestTime' $prev_case >> log.turbo
else
	prep_mesh
	#runParallel potentialFoam -writep -writePhi -initialiseUBCs >> log.turbo
fi

# run
runParallel $application >> log.turbo

# reconstruct
runApplication reconstructPar -latestTime >> log.turbo

# cleanup
rm -rf ${prev_case}/processor*
)"
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
