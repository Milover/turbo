/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::SectionExtensionFactor

Description
	Class SectionExtensionFactor.

	Number of chord lengths in the streamwise direction from the LE/TE point
	at which to place the inlet/outlet.

	Defaults to 1.5.

SourceFiles
	SectionExtensionFactor.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_SECTION_EXTENSION_FACTOR_H
#define INPUT_SECTION_EXTENSION_FACTOR_H

#include "General.h"
#include "PositiveValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class SectionExtensionFactor Declaration
\*---------------------------------------------------------------------------*/

class SectionExtensionFactor final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"SectionExtensionFactor"};


	// Constructors

		//- Default constructor
		SectionExtensionFactor() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit SectionExtensionFactor(const Float f);


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
