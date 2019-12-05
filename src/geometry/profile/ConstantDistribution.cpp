/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>

#include "ConstantDistribution.h"
#include "InputObjectBase.h"
#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void ConstantDistribution::buildInputMap() noexcept
{
	store("maxThickness", NAN);	// [-] - % of chord
}


void ConstantDistribution::check() const
{
	if
	(
		!isInRange(get("maxThickness"), 0.0, 1.0)
	)
		THROW_RUNTIME_ERROR("value of keyword 'maxThickness' out of range [0, 1]");
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

ConstantDistribution::ConstantDistribution(const Stringmap<>& input)
{
	buildInputMap();
	parse(input);
	check();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

double ConstantDistribution::getThicknessAt(const double) const noexcept
{
	return 0.5 * get("maxThickness");
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
