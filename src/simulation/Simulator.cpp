/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <utility>

#include "Simulator.h"

#include "Error.h"
#include "FoamCaseContents.h"
#include "General.h"
#include "Registry.h"
#include "TurboCaseTemplate.h"
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Path Simulator::createCase(const Path& parentCwd)
{
	if (!std::filesystem::is_directory(parentCwd))
		error(FUNC_INFO, parentCwd, " is not a directory");

	String caseName
	{
		"case_" + std::to_string(simId)
	};
	Path caseDir {parentCwd / caseName};

	if (std::filesystem::exists(caseDir))
		error(FUNC_INFO, "case directory: ", caseDir, " already exists");

	// create a case template if necessary
	Simulator::createCaseTemplate();

	std::filesystem::copy
	(
		std::filesystem::current_path() / foam::turboCaseTemplatePath,
		caseDir,
		std::filesystem::copy_options::recursive
	);

	return caseDir;
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Simulator::Simulator
(
	const input::Registry& reg,
	const std::size_t id,
	const Path& parentCwd
)
:
	data_
	{
		&const_cast<input::Registry&>(reg)
	},
	simId {id},
	caseDirectory {createCase(parentCwd)}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Simulator::createCaseTemplate()
{
	Path cwd {std::filesystem::current_path()};

	// don't create if we already have one
	Path localCaseTemplate {cwd / foam::turboCaseTemplatePath};
	if
	(
		std::filesystem::is_directory(localCaseTemplate)
	)
		return;

	for (const auto& [name, contents] : foam::turboCaseTemplateArray)
	{
		// directories will have empty contents
		if (contents.empty())
		{
			std::filesystem::create_directory(cwd / name);
		}
		else
		{
			std::ofstream ofs {cwd / name};

			ofs << contents;
		}
	}
}


void Simulator::simulate()
{
	// check if a foam version exists and is loaded into env
	char* foam {std::getenv("WM_PROJECT")};
	if (!foam)
		error
		(
			FUNC_INFO,
			"Environment variable \"WM_PROJECT\" undefined.\n",
			"Load an OpenFOAM version into the environment to run simulations."
		);

	// check if we have a case directory
	if (!std::filesystem::exists(caseDirectory))
		error(FUNC_INFO, "case directory: ", caseDirectory, " doesn't exist");

	// check if run script is present
	auto turboRun {caseDirectory / foam::turboRunPath.filename()};
	if
	(
		!std::filesystem::exists(turboRun)
	 || !std::filesystem::is_regular_file(turboRun)
	)
		error(FUNC_INFO, "script ", turboRun, " not present");

	// make executable
	std::filesystem::permissions
	(
		turboRun,
		std::filesystem::perms::all,
		std::filesystem::perm_options::add
	);

	writeTurboValues();

	// run sim
	auto cmd {turboRun.c_str()};
	if (std::system(cmd) != EXIT_SUCCESS)
		error
		(
			FUNC_INFO, "command: ", cmd, " exited with ", EXIT_FAILURE
		);
}


void Simulator::writeTurboValues() const
{
	std::ofstream file
	{
		caseDirectory / turboValues,
		std::ios_base::out
	};

	file <<
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       IOobject;
    object      turbo_values;
}

)";
	// this is dumb
	massPrint
	(
		file, 40, " ", ";\n",
		// general
		data_->cref<input::InletRefPoint>(),
		data_->cref<input::TranslationPerTop>(),
		data_->cref<input::TranslationPerBot>(),
		// main 
		data_->cref<input::Density>(),
		data_->cref<input::DynamicViscosity>(),
		data_->cref<input::KinematicViscosity>(),
		data_->cref<input::BladeVelocity>(),
		data_->cref<input::InletRelativeVelocity>(),
		data_->cref<input::StaticPressureDifference>(),
		// turbulence
		data_->cref<input::TurbulenceIntensity>(),
		data_->cref<input::TurbulenceReferenceLengthScale>(),
		data_->cref<input::TurbulenceKineticEnergy>(),
		data_->cref<input::TurbulenceDissipationRate>(),
		data_->cref<input::TurbulenceSpecificDissipationRate>(),
		data_->cref<input::TurbulenceViscosity>(),
		// postprocessing
		data_->cref<input::TEMonitoringPlane>(),
		data_->cref<input::TEMonitoringPlane>()
	);

	file << "\n#inputMode merge\n";
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace simulation
} // End namespace turbo

// ************************************************************************* //
