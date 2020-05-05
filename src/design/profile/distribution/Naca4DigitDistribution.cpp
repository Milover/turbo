/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "Naca4DigitDistribution.h"

#include "Error.h"
#include "General.h"
#include "Utility.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

Naca4DigitDistribution::Naca4DigitDistribution()
:
	max_
	{
		input::read<input::MaxProfileThickness>()
	}
{
	// scale coefficients
	for (auto& a : a_)
		a *= scale_ * max_.value();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float Naca4DigitDistribution::thickness(const Float x) const noexcept(ndebug)
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		error(FUNC_INFO, x, " out of range [0, 1]");

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
