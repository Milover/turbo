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

#include "Geometry.h"
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

		Profile profile;


	// Constructors

		//- Construct from a radius.
		//	Assumes necessary input will be available
		//	from InputRegistry.
		explicit Airfoil(const input::Radius& r);

		//- Construct from a radius and a registry.
		//	Assumes necessary input will be available
		//	from the supplied Registry.
		Airfoil
		(
			const input::Radius& r,
			const input::Registry& reg
		);

		//- Construct from a radius and a registry,
		//	create a model as well.
		//	Assumes necessary input will be available
		//	from the supplied Registry.
		Airfoil
		(
			const input::Radius& r,
			const input::Registry& reg,
			geometry::Model&& mod
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
