/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::DeviationAngle

Description
	Class DeviationAngle.

	Defaults to 0.0.

SourceFiles
	DeviationAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_DEVIATION_ANGLE_H
#define INPUT_DEVIATION_ANGLE_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class DeviationAngle Declaration
\*---------------------------------------------------------------------------*/

class DeviationAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"DeviationAngle"};


	// Constructors

		//- Default constructor
		DeviationAngle() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit DeviationAngle(const Float f);


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
