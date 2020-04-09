/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "Error.h"
#include "General.h"
#include "InputRegistry.h"
#include "Naca4DigitDistribution.h"
#include "StringConverter.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca4DigitDistribution::Naca4DigitDistribution
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

	// scale coefficients
	for (auto& a : a_)
		a *= scale_ * maxThickness_;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Naca4DigitDistribution::thickness(const Float x) const noexcept
{
	return a_[0] * std::sqrt(x) +
		   a_[1] * x +
		   a_[2] * std::pow(x, 2) +
		   a_[3] * std::pow(x, 3) +
		   a_[4] * std::pow(x, 4);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
