/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::ShroudRadius

Description
	Class ShroudRadius.

SourceFiles
	ShroudRadius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SHROUD_RADIUS_H
#define INPUT_SHROUD_RADIUS_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class ShroudRadius Declaration
\*---------------------------------------------------------------------------*/

class ShroudRadius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"ShroudRadius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit ShroudRadius(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
