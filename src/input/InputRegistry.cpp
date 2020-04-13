/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <type_traits>
#include <utility>

#include "InputRegistry.h"

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool InputRegistry::empty() noexcept
{
	return InputRegistry::data_.empty();
}


String InputRegistry::get(const String& key)
{
	auto search {InputRegistry::data_.find(key)};

	if (search == InputRegistry::data_.end())
		THROW_ARGUMENT_ERROR("key '" + key + "' does not exist");

	return search->second;
}


bool InputRegistry::has(const String& key) noexcept
{
	auto search {InputRegistry::data_.find(key)};

	if (search == InputRegistry::data_.end())
		return false;

	return true;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
