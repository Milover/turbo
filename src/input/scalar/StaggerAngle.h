/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::StaggerAngle

Description
	Class StaggerAngle.

SourceFiles
	StaggerAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_STAGGER_ANGLE_H
#define INPUT_STAGGER_ANGLE_H

#include "BladeVelocity.h"
#include "General.h"
#include "IncidenceAngle.h"
#include "InclinationAngle.h"
#include "InletVelocity.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class StaggerAngle Declaration
\*---------------------------------------------------------------------------*/

class StaggerAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"StaggerAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit StaggerAngle(const Float f);

		//- Compute and construct
		StaggerAngle
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const InclinationAngle& zeta,
			const IncidenceAngle& i
		);

		//- Compute assuming zero incidence and construct
		StaggerAngle
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const InclinationAngle& zeta
		);


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
