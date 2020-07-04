/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BladeEfficiency

Description
	Class BladeEfficiency.

	Defaults to 1.0.

SourceFiles
	BladeEfficiency.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BLADE_EFFICIENCY_H
#define INPUT_BLADE_EFFICIENCY_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class BladeEfficiency Declaration
\*---------------------------------------------------------------------------*/

class BladeEfficiency final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"BladeEfficiency"};


	// Constructors

		//- Default constructor
		BladeEfficiency() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit BladeEfficiency(const Float f);


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
