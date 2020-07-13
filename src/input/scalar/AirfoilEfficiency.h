/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::AirfoilEfficiency

Description
	Class AirfoilEfficiency.

SourceFiles
	AirfoilEfficiency.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_AIRFOIL_EFFICIENCY_H
#define INPUT_AIRFOIL_EFFICIENCY_H

#include "AirfoilTotalForce.h"
#include "BladeVelocity.h"
#include "General.h"
#include "InletVelocity.h"
#include "Pitch.h"
#include "PositiveValue.h"
#include "TotalPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class AirfoilEfficiency Declaration
\*---------------------------------------------------------------------------*/

class AirfoilEfficiency final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"AirfoilEfficiency"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit AirfoilEfficiency(const Float f);

		//- Construct from a Float,
		//  no aditional checking required
		AirfoilEfficiency
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const AirfoilTotalForce& F_tot,
			const TotalPressureDifference& dp_tot,
			const Pitch& l
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
