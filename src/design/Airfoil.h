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
#include "Model.h"
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

	// Private data

		const Integer stationNo_;


	// Member functions

		//- Construct the component
		void construct();


public:

	// Public data

		Profile profile;


	// Constructors

		//- Default construct from a station number,
		//	creates an owned registry and creates a model
		explicit Airfoil
		(
			const Integer stationNo = 0,
			const Path& file = Path {}
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	creates an owned model.
		Airfoil
		(
			const Integer stationNo,
			const input::Registry& reg,
			const Path& file = Path {}
		);

		//- Construct from a station number with (owner) registry,
		//	creates a non-owned accessible registry and
		//	takes or shares ownership of a model
		template<typename T>
		Airfoil
		(
			const Integer stationNo,
			const input::Registry& reg,
			T&& model,
			const Path& file = Path {}
		);


	// Member functions

		//- Build geometry
		void build();

		//- Run simulation, return the simulation directory
		[[nodiscard]] Path simulate
		(
			Sptr<mesh::ProfileMesh> mesh = Sptr<mesh::ProfileMesh> {}
		);

		//- Write the mesh in .step format
		//	NOTE: activates the (local) model
		//	FIXME: placeholder implementation
		void write() const override;

};


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<typename T>
Airfoil::Airfoil
(
	const Integer stationNo,
	const input::Registry& reg,
	T&& model,
	const Path& file
)
:
	TurboBase
	{
		reg,
		std::forward<T>(model),
		file
	},
	stationNo_ {stationNo}
{
	setFile("airfoil", ".step");

	construct();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
