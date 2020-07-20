/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::HubRadius

Description
	Class HubRadius.

SourceFiles
	HubRadius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_HUB_RADIUS_H
#define INPUT_HUB_RADIUS_H

#include "BladeEfficiency.h"
#include "Density.h"
#include "General.h"
#include "PositiveValue.h"
#include "RootOutletVelocity.h"
#include "Rps.h"
#include "ShroudRadius.h"
#include "TargetStaticPressureDifference.h"
#include "VortexDistributionExponent.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class RootOutletVelocity;

/*---------------------------------------------------------------------------*\
						Class HubRadius Declaration
\*---------------------------------------------------------------------------*/

class HubRadius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"HubRadius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit HubRadius(const Float f);

		//- Compute and construct
		HubRadius
		(
			const RootOutletVelocity& c_2_h,
			const TargetStaticPressureDifference& dp_req,
			const BladeEfficiency& eta,
			const Rps& rps,
			const VortexDistributionExponent& n,
			const ShroudRadius& r_s,
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
