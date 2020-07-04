/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::AirfoilTotalForce

Description
	Class AirfoilTotalForce.

SourceFiles
	AirfoilTotalForce.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_AIRFOIL_TOTAL_FORCE_H
#define INPUT_AIRFOIL_TOTAL_FORCE_H

#include "Error.h"
#include "RegistryObject.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class AirfoilTotalForce Declaration
\*---------------------------------------------------------------------------*/

class AirfoilTotalForce final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"AirfoilTotalForce"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit AirfoilTotalForce(const Vector& v) noexcept(ndebug);


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
