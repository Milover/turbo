/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::MaxAbsBladeThickness

Description
	Class MaxAbsBladeThickness.

SourceFiles
	MaxAbsBladeThickness.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_MAX_ABS_BLADE_THICKNESS_H
#define INPUT_MAX_ABS_BLADE_THICKNESS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class MaxAbsBladeThickness Declaration
\*---------------------------------------------------------------------------*/

class MaxAbsBladeThickness final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"MaxAbsBladeThickness"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit MaxAbsBladeThickness(const Float f);


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
