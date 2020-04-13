/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InclinationAngle

Description
	Class InclinationAngle.

SourceFiles
	InclinationAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INCLINATION_ANGLE_H
#define INPUT_INCLINATION_ANGLE_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class InclinationAngle Declaration
\*---------------------------------------------------------------------------*/

class InclinationAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"InclinationAngle"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit InclinationAngle(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
