/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::KinematicViscosity

Description
	Class KinematicViscosity.

SourceFiles
	KinematicViscosity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_KINEMATC_VISCOSITY_H
#define INPUT_KINEMATC_VISCOSITY_H

#include "Density.h"
#include "DynamicViscosity.h"
#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class KinematicViscosity Declaration
\*---------------------------------------------------------------------------*/

class KinematicViscosity final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"KinematicViscosity"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit KinematicViscosity(const Float f);

		//- Compute and construct
		KinematicViscosity
		(
			const Density& rho,
			const DynamicViscosity& mu
		);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
