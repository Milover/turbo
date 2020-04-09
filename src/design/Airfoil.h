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

#include "Profile.h"
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

	// Member functions

		//- Construct the component
		void construct();


public:

	// Public data

		Profile geometry;


	// Constructors

		//- Construct from a radius
		explicit Airfoil(const input::Radius& r);

		//- Construct from a radius and a registry
		Airfoil
		(
			const input::Radius& r,
			const input::Registry& reg
		);


	// Member functions

		//- Build geometry
		void build() final;

		//- Finalize geometry
		void finalize() final;

		//- Build mesh
		void mesh() final;

		//- Parametrize
		void parametrize() final;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
