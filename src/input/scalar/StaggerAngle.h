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
#include "CorrectedValue.h"
#include "General.h"
#include "InclinationAngle.h"
#include "InletVelocity.h"
#include "RegistryObject.h"
#include "Vector.h"

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
	public RegistryObject<Float>,
	public CorrectedValue<Float, StaggerAngle>
{
public:

	friend CVBase;
	using CVBase::correct;


	// Public static data

		inline static const String name {"StaggerAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit StaggerAngle(const Float f);

		//- Compute assuming zero incidence and construct
		StaggerAngle
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const InclinationAngle& zeta
		);


	// Member functions

		//- Compute and add correction
		void correct
		(
			const Vector& stagnationPt,
			const Vector& leadingEdgePt,
			const Vector& profileCentroid
		);

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
