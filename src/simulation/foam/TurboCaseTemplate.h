/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	A static array with all of the file paths and contents required to create
	a turbo_case_template directory.

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_FOAM_TURBO_CASE_TEMPLATE_H
#define SIMULATION_FOAM_TURBO_CASE_TEMPLATE_H

#include "FoamCaseContents.h"
#include "FoamControlDictFile.h"
#include "FoamCreatePatchDictFile.h"
#include "FoamDecomposeParDictFile.h"
#include "FoamEpsilonFile.h"
#include "FoamFieldMinMaxFile.h"
#include "FoamForcesFile.h"
#include "FoamFvSchemesFile.h"
#include "FoamFvSolutionFile.h"
#include "FoamKFile.h"
#include "FoamMapFieldsDictFile.h"
#include "FoamNutFile.h"
#include "FoamOmegaFile.h"
#include "FoamPatchSurfaceFieldValueFile.h"
#include "FoamPFile.h"
#include "FoamSampledSurfaceFieldValueFile.h"
#include "FoamSetSetbatchFile.h"
#include "FoamTransportPropertiesFile.h"
#include "FoamTurbulencePropertiesFile.h"
#include "FoamUFile.h"
#include "FoamYPlusFile.h"
#include "General.h"
#include "TurboRunFile.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{
namespace foam
{
namespace detail
{
	using ps = Pair<Path, String>;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline static const std::array<detail::ps, 26> turboCaseTemplateArray
{
	detail::ps {turboCaseTemplatePath,			""},
	detail::ps {foam0origPath,					""},
	detail::ps {foamConstantPath,				""},
	detail::ps {foamSystemPath,					""},
	detail::ps {turboRunPath,					turboRunFile},
	detail::ps {turboPostPath,					""},

	detail::ps {foamEpsilonPath,				foamEpsilonFile},
	detail::ps {foamKPath,						foamKFile},
	detail::ps {foamNutPath,					foamNutFile},
	detail::ps {foamOmegaPath,					foamOmegaFile},
	detail::ps {foamPPath,						foamPFile},
	detail::ps {foamUPath,						foamUFile},

	detail::ps {foamTransportPropertiesPath,	foamTransportPropertiesFile},
	detail::ps {foamTurbulencePropertiesPath,	foamTurbulencePropertiesFile},

	detail::ps {foamControlDictPath,			foamControlDictFile},
	detail::ps {foamCreatePatchDictPath,		foamCreatePatchDictFile},
	detail::ps {foamDecomposeParDictPath,		foamDecomposeParDictFile},
	detail::ps {foamFvSchemesPath,				foamFvSchemesFile},
	detail::ps {foamFvSolutionPath,				foamFvSolutionFile},
	detail::ps {foamMapFieldsDictPath,			foamMapFieldsDictFile},
	detail::ps {foamSetSetbatchPath,			foamSetSetbatchFile},

	detail::ps {foamFieldMinMaxFilePath,			foamFieldMinMaxFile},
	detail::ps {foamForcesFilePath,					foamForcesFile},
	detail::ps {foamPatchSurfaceFieldValuePath,		foamPatchSurfaceFieldValueFile},
	detail::ps {foamSampledSurfaceFieldValuePath,	foamSampledSurfaceFieldValueFile},
	detail::ps {foamYPlusPath,						foamYPlusFile}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace foam
} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
