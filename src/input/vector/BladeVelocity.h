/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BladeVelocity

Description
	Class BladeVelocity.

SourceFiles
	BladeVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BLADE_VELOCITY_H
#define INPUT_BLADE_VELOCITY_H

#include "Error.h"
#include "RegistryObject.h"
#include "Radius.h"
#include "Rps.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class BladeVelocity Declaration
\*---------------------------------------------------------------------------*/

class BladeVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"BladeVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit BladeVelocity(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		BladeVelocity
		(
			const Rps& rps,
			const Radius& r
		) noexcept(ndebug);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
