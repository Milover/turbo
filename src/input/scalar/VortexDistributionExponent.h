/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::VortexDistributionExponent

Description
	Class VortexDistributionExponent.

	Computed automatically, such that the integral requested work is
	satisfied. Orientational values:

	   -1 - free vortex distribution
		0 - const. vortex distribution
		1 - forced vortex distribution

SourceFiles
	VortexDistributionExponent.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VORTEX_DISTRIBUTION_EXPONENT_H
#define INPUT_VORTEX_DISTRIBUTION_EXPONENT_H

#include <limits>

#include "AerodynamicEfficiency.h"
#include "Density.h"
#include "General.h"
#include "HubRadius.h"
#include "LimitedValue.h"
#include "RootOutletVelocity.h"
#include "Rps.h"
#include "ShroudRadius.h"
#include "StaticPressureDifference.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class StaticPressureDifference;
class RootOutletVelocity;

/*---------------------------------------------------------------------------*\
				Class VortexDistributionExponent Declaration
\*---------------------------------------------------------------------------*/

class VortexDistributionExponent final
:
	// FIXME: this is not good, but we're using it for now
	public LimitedValue<Float, -1, std::numeric_limits<Integer>::max()>
{
public:

	// Public static data

		inline static const String name {"VortexDistributionExponent"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit VortexDistributionExponent(const Float f);

		//- Compute and construct
		VortexDistributionExponent
		(
			const RootOutletVelocity& c_2_h,
			const StaticPressureDifference& dp,
			const AerodynamicEfficiency& eta,
			const Rps& rps,
			const HubRadius& r_h,
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
