/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::DynamicViscosity

Description
	Class DynamicViscosity.

SourceFiles
	DynamicViscosity.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_DYNAMIC_VISCOSITY_H
#define INPUT_DYNAMIC_VISCOSITY_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class DynamicViscosity Declaration
\*---------------------------------------------------------------------------*/

class DynamicViscosity final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"DynamicViscosity"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit DynamicViscosity(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
