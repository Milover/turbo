/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::ShroudSkewAngle

Description
	Class ShroudSkewAngle.

	Defaults to 0.0.

SourceFiles
	ShroudSkewAngle.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SHROUD_SKEW_ANGLE_H
#define INPUT_SHROUD_SKEW_ANGLE_H

#include "General.h"
#include "RegistryObject.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class ShroudSkewAngle Declaration
\*---------------------------------------------------------------------------*/

class ShroudSkewAngle final
:
	public RegistryObject<Float>
{
public:

	// Public static data

		inline static const String name {"ShroudSkewAngle"};


	// Constructors

		//- Default constructor
		ShroudSkewAngle() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit ShroudSkewAngle(const Float f);


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
