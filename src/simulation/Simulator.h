/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::simulation::Simulator

Description
	Class Simulator.

SourceFiles
	Simulator.cpp

\*---------------------------------------------------------------------------*/

#ifndef SIMULATION_SIMULATOR_H
#define SIMULATION_SIMULATOR_H

#include <filesystem>
#include <utility>

#include "FoamCaseContents.h"
#include "General.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace simulation
{

/*---------------------------------------------------------------------------*\
						Class Simulator Declaration
\*---------------------------------------------------------------------------*/

class Simulator
{
private:

	// Private data

		input::Registry* data_;


	// Member functions

		//- Create an openfoam case in 'parentCwd'
		[[nodiscard]] Path createCase(const Path& parentCwd);


public:

	// Public data

		const std::size_t simId;
		const Path caseDirectory;

		inline static const Path turboValues {"turbo_values"};
		inline static const Path caseTemplate {foam::turboCaseTemplatePath};


	// Constructors

		//- Construct from a registry and a mesh file path
		Simulator
		(
			const input::Registry& reg,
			const std::size_t id = 0,
			const Path& parentCwd = std::filesystem::current_path()
		);

		//- Disallow copy construction
		Simulator(const Simulator&) = delete;

		//- Move constructor
		Simulator(Simulator&&) = default;


	//- Destructor
	~Simulator() = default;


	// Member functions

		//- Create an openfoam case template at the program root directory
		static void createCaseTemplate();

		//- Run simulation
		void simulate();

		//- Write boundary condition include file
		void writeTurboValues() const;


	// Member operators

		//- Disallow copy assignment
		Simulator& operator=(const Simulator&) = delete;

		//- Disallow move assignment
		Simulator& operator=(Simulator&&) = delete;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace simulation
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
