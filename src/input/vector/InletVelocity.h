/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InletVelocity

Description
	Class InletVelocity.

SourceFiles
	InletVelocity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INLET_VELOCITY_H
#define INPUT_INLET_VELOCITY_H

#include "HubRadius.h"
#include "RegistryObject.h"
#include "ShroudRadius.h"
#include "Vector.h"
#include "VolumeFlowRate.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class InletVelocity Declaration
\*---------------------------------------------------------------------------*/

class InletVelocity final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"InletVelocity"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit InletVelocity(const Vector& v);

		//- Compute and construct
		InletVelocity
		(
			const VolumeFlowRate& Q,
			const HubRadius& r_h,
			const ShroudRadius& r_s
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
