/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::OutletVelocity

Description
	Class OutletVelocity.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_OUTLET_VELOCITY_H
#define INPUT_OUTLET_VELOCITY_H

#include <type_traits>
#include <utility>

#include "BladeVelocity.h"
#include "General.h"
#include "HubRadius.h"
#include "InitialDesign.h"
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

/*---------------------------------------------------------------------------*\
						Class OutletVelocity Definition
\*---------------------------------------------------------------------------*/

class OutletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const Word name {"OutletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		template
		<
			typename T,
			std::enable_if_t<std::is_same_v<Vector, T>, int> = 0>
		>
		explicit OutletVelocity(T&& t)
		:
			RegBase {std::forward<T>(t)}
		{}

		//- Compute and construct
		OutletVelocity
		(
			const RootOutletVelocity& c_2_h,
			const VortexDistributionExponent& n,
			const Radius& r,
			const HubRadius& r_h
		)
		:
			OutletVelocity
			{
				compute::computeVortexDistributionVelocity
				(
					c_2_h.value(),
					n.value(),
					r.value(),
					r_h.value()
				)
			}
		{}

		//- Compute by applying deHaller criterion and construct
		OutletVelocity
		(
			const InletVelocity& c_1,
			const RootOutletVelocity& c_2_h,
			const VortexDistributionExponent& n,
			const Radius& r,
			const HubRadius& r_h
			const BladeVelocity& U
		)
		:
			OutletVelocity
			{
				compute::deHaller
				(
					c_1.value(),
					compute::computeVortexDistributionVelocity
					(
						c_2_h.value(),
						n.value(),
						r.value(),
						r_h.value()
					),
					U.value()
				)
			}
		{}

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
