/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <type_traits>
#include <utility>

#include "Error.h"
#include "General.h"
#include "InputRegistry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool InputRegistry::empty() noexcept
{
	return data_.empty();
}


Word InputRegistry::get(const Word& key)
{
	auto search {data_.find(key)};

	if (search == data_.end())
		THROW_ARGUMENT_ERROR("key '" + key + "' does not exist");

	return search->second;
}


bool InputRegistry::has(const Word& key) noexcept
{
	auto search {data_.find(key)};

	if (search == data_.end())
		return false;

	return true;
}


template<typename T>
std::enable_if_t
<
	std::is_same_v<T, Map<Word>>
 || std::is_same_v<T, HashMap<Word>>,
	void
>
store(T&& input)
{
	if constexpr (std::is_same_v<T, Map<Word>>)
		for (auto&& p : std::forward<T>(input))
			data_.insert
			(
				std::forward<decltype(p)>(p)
			);
	else
		data_ = std::forward<T>(input);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
