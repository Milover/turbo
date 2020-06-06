/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "ConstantThickness.h"

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "ThicknessGeneratorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ConstantThickness::ConstantThickness(const input::Registry& reg)
:
	ThicknessGeneratorBase {reg}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float ConstantThickness::thickness(const Float x) const noexcept(ndebug)
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		error(FUNC_INFO, x, " out of range [0, 1]");

	return 0.5 * max_.value();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
