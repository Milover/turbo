/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::CamberAngle

Description
	Class CamberAngle.

Sourcefiles
	CamberAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_CAMBER_ANGLE_H
#define INPUT_CAMBER_ANGLE_H

#include "BladeVelocity.h"
#include "General.h"
#include "IncidenceAngle.h"
#include "InletVelocity.h"
#include "OutletVelocity.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class CamberAngle Declaration
\*---------------------------------------------------------------------------*/

class CamberAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"CamberAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit CamberAngle(const Float f);

		//- Compute and construct
		CamberAngle
		(
			const InletVelocity& c_1,
			const OutletVelocity& c_2,
			const BladeVelocity& U,
			const IncidenceAngle& i
		);

		//- Compute assuming zero incidence and construct
		CamberAngle
		(
			const InletVelocity& c_1,
			const OutletVelocity& c_2,
			const BladeVelocity& U
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
