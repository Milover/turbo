/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "CamberPointSpacing.h"

#include "Error.h"
#include "General.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

CamberPointSpacing::Type CamberPointSpacing::convert(String& s) const
{
	// trim whitespace
	trimWhiteLR(s);

	if (s == "Linear")
		return Type::LINEAR;
	else if (s == "Cosine")
		return Type::COSINE;
	else
		error(FUNC_INFO, "unknown CamberPointSpacing: ", s);
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

CamberPointSpacing::CamberPointSpacing() noexcept
:
	RegBase {Type::COSINE}
{}


CamberPointSpacing::CamberPointSpacing(String s)
:
	RegBase {convert(s)}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
