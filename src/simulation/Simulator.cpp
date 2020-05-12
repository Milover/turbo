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
#include "General.h"
#include "Registry.h"
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Simulator::Simulator
(
	const input::Registry& reg,
	const Path& caseDir,
	const Path& mshfile
)
:
	data_
	{
		&const_cast<input::Registry&>(reg)
	},
	caseDirectory {caseDir},
	meshfile {mshfile}
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

	// check if we have a mesh
	if (!std::filesystem::exists(caseDirectory / meshfile.filename()))
		error
		(
			FUNC_INFO,
			"mesh file: ", caseDirectory / meshfile.filename(), " doesn't exist"
		);

	++Simulator::simId_;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Path Simulator::createCase(const Path& location)
{
	if (!std::filesystem::is_directory(location))
		error(FUNC_INFO, "location: ", location, " is not a directory");

	String caseName
	{
		"case_" + std::to_string(Simulator::simId_)
	};
	Path caseDir {location / caseName};

	if (std::filesystem::exists(caseDir))
		error(FUNC_INFO, "case directory: ", caseDir, " already exists");

	Simulator::createCaseTemplate();

	std::filesystem::copy
	(
		std::filesystem::current_path() / caseTemplate,
		caseDir,
		std::filesystem::copy_options::recursive
	);

	return caseDir;
}


void Simulator::createCaseTemplate()
{
	// check if turbo is loaded
	char* turboSrc {std::getenv("TURBO_SRC_DIR")};
	if (!turboSrc)
		error
		(
			FUNC_INFO,
			"Environment variable \"TURBO_SRC_DIR\" undefined.\n",
			"Load 'turbo' into the environment to access function."
		);

	// check if we have a global template
	Path globalCaseTemplate {Path {turboSrc} / "share" / caseTemplate};
	if
	(
		!std::filesystem::is_directory(globalCaseTemplate)
	)
		error
		(
			FUNC_INFO,
			"global case template: ", globalCaseTemplate, " doesn't exist"
		);

	// don't copy if we already have one
	Path localCaseTemplate {std::filesystem::current_path() / caseTemplate};
	if
	(
		!std::filesystem::is_directory(localCaseTemplate)
	)
	std::filesystem::copy
	(
		globalCaseTemplate,
		localCaseTemplate,
		std::filesystem::copy_options::recursive
	);
}


void Simulator::simulate()
{
	writeTurboValues();

	auto sysCmd = [](auto&& cmd) -> void
	{
		using Cmd = decltype(cmd);

		auto cmdExit {std::system(std::forward<Cmd>(cmd))};

		if (cmdExit != EXIT_SUCCESS)
			error
			(
				FUNC_INFO, "command: ", cmd, " exited with ", EXIT_FAILURE
			);
	};

	// check if run script is present
	if
	(
		!std::filesystem::is_regular_file(caseDirectory / turboRun)
	)
		error(FUNC_INFO, "script ", caseDirectory / turboRun, " not present");

	// make executable
	std::filesystem::permissions
	(
		caseDirectory / turboRun,
		std::filesystem::perms::all,
		std::filesystem::perm_options::add
	);

	// run sim
	sysCmd
	(
		std::filesystem::absolute(caseDirectory / turboRun).c_str()
	);
}


void Simulator::writeTurboValues() const
{
	Path includeFile {caseDirectory / turboValues};
	std::ofstream file {includeFile, std::ios_base::out};

	file <<
R"(FoamFile
{
    version     2.0;
    format      ascii;
    class       IOobject;
    object      turbo_values;
}

)";
	massPrint
	(
		file, 40, " ", ";\n",
		data_->cref<input::TranslationPerBot>(),
		data_->cref<input::TranslationPerTop>(),
		data_->cref<input::KinematicViscosity>(),
		data_->cref<input::InletRelativeVelocity>(),
		data_->cref<input::TotalPressureDifference>(),
		data_->cref<input::TurbulenceIntensity>(),
		data_->cref<input::TurbulenceReferenceLengthScale>(),
		data_->cref<input::TurbulenceKineticEnergy>(),
		data_->cref<input::TurbulenceDissipationRate>(),
		data_->cref<input::TurbulenceSpecificDissipationRate>(),
		data_->cref<input::TurbulenceViscosity>()
	);


	file <<
R"(
#inputMode merge
)";
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace simulation
} // End namespace turbo

// ************************************************************************* //
