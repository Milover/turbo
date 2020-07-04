/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::StaticPressureDifference

Description
	Class StaticPressureDifference.

SourceFiles
	StaticPressureDifference.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_STATIC_PRESSURE_DIFFERENCE_H
#define INPUT_STATIC_PRESSURE_DIFFERENCE_H

#include "BladeEfficiency.h"
#include "BladeVelocity.h"
#include "Density.h"
#include "General.h"
#include "InletVelocity.h"
#include "PositiveValue.h"
#include "OutletVelocity.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class OutletVelocity;

/*---------------------------------------------------------------------------*\
					Class StaticPressureDifference Declaration
\*---------------------------------------------------------------------------*/

class StaticPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"StaticPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit StaticPressureDifference(const Float f);

		//- Compute and construct
		StaticPressureDifference
		(
			const InletVelocity& c_1,
			const OutletVelocity& c_2,
			const BladeVelocity& U,
			const BladeEfficiency& eta,
			const Density& rho
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
