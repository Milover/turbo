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
#include "TotalPressureDifference.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// Forward declarations
class TotalPressureDifference;

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

		//- Compute and construct
		RootOutletVelocity
		(
			const InletVelocity& c_1,
			const TotalPressureDifference& dp,
			const Rps& rps,
			const HubRadius& r_h,
			const Density& rho
		) noexcept(ndebug);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
