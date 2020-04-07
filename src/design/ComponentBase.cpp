/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <string>

#include "ComponentBase.h"
#include "Error.h"
#include "InputObjectBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

double ComponentBase::convert(const std::string& value) const
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

double ComponentBase::get(const std::string& key) const
{
	if (hasValue(key))
		return InputObjectBase::get(key);
	else if (owner_ != nullptr)
		return owner_->get(key);
	else
		THROW_ARGUMENT_ERROR("key '" + key + "' does not exist");
}


bool ComponentBase::hasValue(const std::string& key) const noexcept
{
	if
	(
		hasKey(key) &&
		!std::isnan(InputObjectBase::get(key))
	)
		return true;
	
	return false;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// ************************************************************************* //
