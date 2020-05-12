/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TurbulenceIntensity

Description
	Class TurbulenceIntensity.

	Defaults to 0.05.

SourceFiles
	TurbulenceIntensity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TURBULENCE_INTENSITY_H
#define INPUT_TURBULENCE_INTENSITY_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class TurbulenceIntensity Declaration
\*---------------------------------------------------------------------------*/

class TurbulenceIntensity final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"TurbulenceIntensity"};


	// Constructors

		//- Default constructor
		TurbulenceIntensity() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit TurbulenceIntensity(const Float f);


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
