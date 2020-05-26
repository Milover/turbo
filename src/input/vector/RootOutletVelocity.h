/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RootOutletVelocity

Description
	Class RootOutletVelocity.

SourceFiles
	RootOutletVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_ROOT_OUTLET_VELOCITY_H
#define INPUT_ROOT_OUTLET_VELOCITY_H

#include "Density.h"
#include "Error.h"
#include "HubRadius.h"
#include "InletVelocity.h"
#include "RegistryObject.h"
#include "Rps.h"
#include "StaticPressureDifference.h"
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

		//- Compute by applying the de Haller criterion and construct
		RootOutletVelocity
		(
			const InletVelocity& c_1,
			const StaticPressureDifference& dp,
			const Rps& rps,
			const HubRadius& r_h,
			const Density& rho
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
