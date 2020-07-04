/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::OutletRelativeVelocity

Description
	Class OutletRelativeVelocity.

SourceFiles
	OutletRelativeVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_OUTLET_RELATIVE_VELOCITY_H
#define INPUT_OUTLET_RELATIVE_VELOCITY_H

#include "Error.h"
#include "General.h"
#include "RegistryObject.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class OutletRelativeVelocity Declaration
\*---------------------------------------------------------------------------*/

class OutletRelativeVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"OutletRelativeVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit OutletRelativeVelocity(const Vector& v) noexcept(ndebug);


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
