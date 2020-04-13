/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "ConstantDistribution.h"

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

ConstantDistribution::ConstantDistribution()
:
	max_
	{
		input::read<input::MaxProfileThickness>()
	}
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Float ConstantDistribution::thickness(const Float x) const
{
	if
	(
		!isInRange(x, 0.0, 1.0)
	)
		THROW_DOMAIN_ERROR("x out of range [0, 1]");

	return 0.5 * max_.value();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
