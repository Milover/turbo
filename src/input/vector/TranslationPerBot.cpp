/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TranslationPerBot.h"

#include "Error.h"
#include "Pitch.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TranslationPerBot::TranslationPerBot(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


TranslationPerBot::TranslationPerBot(const Pitch& l) noexcept(ndebug)
:
	TranslationPerBot
	{
		Vector {0.0, l.value(), 0.0}
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TranslationPerBot::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
