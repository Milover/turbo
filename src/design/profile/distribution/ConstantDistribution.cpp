/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "ConstantDistribution.h"
#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "StringConverter.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ConstantDistribution::ConstantDistribution()
:
	maxThickness_
	{
		StringConverter<Float> {}
		(
			InputRegistry::get("maxThickness")
		)
	}
{
	if
	(
		!isInRange(maxThickness_, 0.0, 1.0)
	)
		THROW_RUNTIME_ERROR("maxThickness out of range [0, 1]");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float ConstantDistribution::thickness(const Float x) const noexcept
{
	return 0.5 * maxThickness_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
