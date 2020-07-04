/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TargetStaticPressureDifference

Description
	Class TargetStaticPressureDifference.

SourceFiles
	TargetStaticPressureDifference.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TARGET_STATIC_PRESSURE_DIFFERENCE_H
#define INPUT_TARGET_STATIC_PRESSURE_DIFFERENCE_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TargetStaticPressureDifference Declaration
\*---------------------------------------------------------------------------*/

class TargetStaticPressureDifference final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"TargetStaticPressureDifference"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit TargetStaticPressureDifference(const Float f);


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
