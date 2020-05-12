/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TranslationPerBot

Description
	Class TranslationPerBot.

SourceFiles
	TranslationPerBot.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TRANSLATION_PER_BOT_H
#define INPUT_TRANSLATION_PER_BOT_H

#include "Error.h"
#include "RegistryObject.h"
#include "Pitch.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class TranslationPerBot Declaration
\*---------------------------------------------------------------------------*/

class TranslationPerBot final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"TranslationPerBot"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit TranslationPerBot(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		TranslationPerBot(const Pitch& l) noexcept(ndebug);


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
