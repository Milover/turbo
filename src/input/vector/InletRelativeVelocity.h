/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InletRelativeVelocity

Description
	Class InletRelativeVelocity.

SourceFiles
	InletRelativeVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INLET_RELATIVE_VELOCITY_H
#define INPUT_INLET_RELATIVE_VELOCITY_H

#include "BladeVelocity.h"
#include "Error.h"
#include "General.h"
#include "InletVelocity.h"
#include "RegistryObject.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class InletRelativeVelocity Declaration
\*---------------------------------------------------------------------------*/

class InletRelativeVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"InletRelativeVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit InletRelativeVelocity(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		InletRelativeVelocity
		(
			const InletVelocity& c_1,
			const BladeVelocity& U
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
