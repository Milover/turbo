/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RootOutletVelocity

Description
	Class RootOutletVelocity.

	Swirl velocity at mean radius, used to prescribe the swirl distribution.

SourceFiles
	RootOutletVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_ROOT_OUTLET_VELOCITY_H
#define INPUT_ROOT_OUTLET_VELOCITY_H

#include "AerodynamicEfficiency.h"
#include "Error.h"
#include "HubRadius.h"
#include "InletVelocity.h"
#include "RegistryObject.h"
#include "Rps.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class StaticPressureDifference;

/*---------------------------------------------------------------------------*\
					Class RootOutletVelocity Declaration
\*---------------------------------------------------------------------------*/

class RootOutletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"RootOutletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit RootOutletVelocity(const Vector& v) noexcept(ndebug);

		//- Compute and apply the de Haller criterion and construct,
		//	computed by requiring the root pressure rise to be maximal
		RootOutletVelocity
		(
			const InletVelocity& c_1,
			const AerodynamicEfficiency& eta,
			const Rps& N,
			const HubRadius& r_h
		) noexcept(ndebug);


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
