/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Airfoil

Description
	Class Airfoil

SourceFiles
	Airfoil.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_AIRFOIL_H
#define DESIGN_AIRFOIL_H

#include <utility>

#include "General.h"
#include "Profile.h"
#include "ProfileMesh.h"
#include "Registry.h"
#include "TurboBase.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class Airfoil Declaration
\*---------------------------------------------------------------------------*/

class Airfoil final
:
	public TurboBase
{
private:

	// Public data

		std::size_t simId_ {0};


	// Member functions

		//- Construct the component
		void construct
		(
			const input::Radius& radius,
			const input::DeviationAngle& delta
		);


public:

	// Public data

		Profile profile;


	// Constructors

		//- Default construct from a station number,
		//	creates an owned registry and creates a model
		explicit Airfoil
		(
			const input::Radius& radius,
			const input::DeviationAngle& delta = input::DeviationAngle {},
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		Airfoil
		(
			const input::Radius& radius,
			const input::Registry& reg,
			const input::DeviationAngle& delta = input::DeviationAngle {},
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename T>
		Airfoil
		(
			const input::Radius& radius,
			const input::Registry& reg,
			T&& model,
			const input::DeviationAngle& delta = input::DeviationAngle {},
			const Path& parentCwd = std::filesystem::current_path(),
			const std::size_t id = 0
		);


	// Member functions

		//- Build geometry
		void build();

		//- Build mesh
		Sptr<mesh::ProfileMesh> mesh(const bool writeMesh = false) const;

		//- Run simulation, return the simulation directory
		Path simulate
		(
			Sptr<mesh::ProfileMesh> mesh = Sptr<mesh::ProfileMesh> {}
		);

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
Airfoil::Airfoil
(
	const input::Radius& radius,
	const input::Registry& reg,
	T&& model,
	const input::DeviationAngle& delta,
	const Path& parentCwd,
	const std::size_t id
)
:
	TurboBase
	{
		"airfoil.step",
		reg,
		std::forward<T>(model),
		parentCwd,
		id
	}
{
	construct(radius, delta);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
