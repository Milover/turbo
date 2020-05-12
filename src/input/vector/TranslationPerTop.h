/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::TranslationPerTop

Description
	Class TranslationPerTop.

SourceFiles
	TranslationPerTop.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_TRANSLATION_PER_TOP_H
#define INPUT_TRANSLATION_PER_TOP_H

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
					Class TranslationPerTop Declaration
\*---------------------------------------------------------------------------*/

class TranslationPerTop final
:
	public RegistryObject<Vector>
{
public:

	// Public static data

		inline static const String name {"TranslationPerTop"};


	// Constructors

		//- Construct from a Vector,
		//  no aditional checking required
		explicit TranslationPerTop(const Vector& v) noexcept(ndebug);

		//- Compute and construct
		TranslationPerTop(const Pitch& l) noexcept(ndebug);


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
