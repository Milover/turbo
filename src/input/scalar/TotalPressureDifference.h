/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TotalPressureDifference

Description
	Class TotalPressureDifference.

SourceFiles
	TotalPressureDifference.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TOTAL_PRESSURE_DIFFERENCE_H
#define INPUT_TOTAL_PRESSURE_DIFFERENCE_H

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
					Class TotalPressureDifference Declaration
\*---------------------------------------------------------------------------*/

class TotalPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TotalPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TotalPressureDifference(const Float f);

		//- Compute and construct
		TotalPressureDifference
		(
			const InletVelocity& c_1,
			const OutletVelocity& c_2,
			const BladeVelocity& U,
			const Density& rho
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
