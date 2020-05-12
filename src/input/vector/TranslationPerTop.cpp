/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "TranslationPerTop.h"

#include "Error.h"
#include "Pitch.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

TranslationPerTop::TranslationPerTop(const Vector& v) noexcept(ndebug)
:
	RegBase {v}
{}


TranslationPerTop::TranslationPerTop(const Pitch& l) noexcept(ndebug)
:
	TranslationPerTop
	{
		Vector {0.0, -l.value(), 0.0}
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

String TranslationPerTop::getName() const
{
	return name;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
