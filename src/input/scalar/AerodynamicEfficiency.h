/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::AerodynamicEfficiency

Description
	Class AerodynamicEfficiency.

	Guesstimate for the initial design, corrected after simulations are run.

	Defaults to 0.6.

SourceFiles
	AerodynamicEfficiency.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_AERODYNAMIC_EFFICIENCY_H
#define INPUT_AERODYNAMIC_EFFICIENCY_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class AerodynamicEfficiency Declaration
\*---------------------------------------------------------------------------*/

class AerodynamicEfficiency final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"AerodynamicEfficiency"};


	// Constructors

		//- Default constructor
		AerodynamicEfficiency() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit AerodynamicEfficiency(const Float f);


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
