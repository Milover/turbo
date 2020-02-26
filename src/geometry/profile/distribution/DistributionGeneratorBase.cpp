/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <cmath>
#include <string>

#include "DistributionGeneratorBase.h"
#include "Error.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

double DistributionGeneratorBase::convert(const std::string& value) const
{
	try
	{
		return std::stod(value);
	}
	catch (...)
	{
		THROW_ARGUMENT_ERROR("can't convert '" + value + "' to double");
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool DistributionGeneratorBase::hasValue(const std::string& key) const noexcept
{
	if
	(
		hasKey(key) &&
		!std::isnan(get(key))
	)
		return true;
	
	return false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// ************************************************************************* //
