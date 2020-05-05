/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::OutletVelocity

Description
	Class OutletVelocity.

SourceFiles
	OutletVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_OUTLET_VELOCITY_H
#define INPUT_OUTLET_VELOCITY_H

#include "BladeVelocity.h"
#include "Error.h"
#include "HubRadius.h"
#include "InletVelocity.h"
#include "Radius.h"
#include "RegistryObject.h"
#include "RootOutletVelocity.h"
#include "Vector.h"
#include "VortexDistributionExponent.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class RootOutletVelocity;

/*---------------------------------------------------------------------------*\
					Class OutletVelocity Declaration
\*---------------------------------------------------------------------------*/

class OutletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"OutletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit OutletVelocity(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		OutletVelocity
		(
			const RootOutletVelocity& c_2_h,
			const VortexDistributionExponent& n,
			const Radius& r,
			const HubRadius& r_h
		) noexcept(ndebug);

		//- Compute by applying deHaller criterion and construct
		OutletVelocity
		(
			const InletVelocity& c_1,
			const RootOutletVelocity& c_2_h,
			const VortexDistributionExponent& n,
			const Radius& r,
			const HubRadius& r_h,
			const BladeVelocity& U
		) noexcept(ndebug);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
