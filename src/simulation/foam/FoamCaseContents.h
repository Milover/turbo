/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Simulation case directory content paths. Given as relative paths
	from the case root directory.

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_FOAM_CASE_CONTENTS_H
#define SIMULATION_FOAM_FOAM_CASE_CONTENTS_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const Path turboCaseTemplatePath {"turbo_case_template"};


inline static const Path foam0origPath
{
	turboCaseTemplatePath / "0.orig"
};

inline static const Path foamConstantPath
{
	turboCaseTemplatePath / "constant"
};

inline static const Path foamSystemPath
{
	turboCaseTemplatePath / "system"
};

inline static const Path turboRunPath
{
	turboCaseTemplatePath / "turbo_run"
};


inline static const Path foamEpsilonPath
{
	foam0origPath / "epsilon"
};

inline static const Path foamKPath
{
	foam0origPath / "k"
};

inline static const Path foamNutPath
{
	foam0origPath / "nut"
};

inline static const Path foamOmegaPath
{
	foam0origPath / "omega"
};

inline static const Path foamPPath
{
	foam0origPath / "p"
};

inline static const Path foamUPath
{
	foam0origPath / "U"
};


inline static const Path foamTransportPropertiesPath
{
	foamConstantPath / "transportProperties"
};

inline static const Path foamTurbulencePropertiesPath
{
	foamConstantPath / "turbulenceProperties"
};


inline static const Path foamControlDictPath
{
	foamSystemPath / "controlDict"
};

inline static const Path foamCreatePatchDictPath
{
	foamSystemPath / "createPatchDict"
};

inline static const Path foamDecomposeParDictPath
{
	foamSystemPath / "decomposeParDict"
};

inline static const Path foamfvSchemesPath
{
	foamSystemPath / "fvSchemes"
};

inline static const Path foamFvSolutionPath
{
	foamSystemPath / "fvSolution"
};

inline static const Path foamSetSetbatchPath
{
	foamSystemPath / "setSet.batch"
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
