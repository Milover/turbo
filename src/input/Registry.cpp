/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include <memory>
#include <utility>

#include "General.h"
#include "Registry.h"
#include "RegistryObject.h"
#include "RegistryObjectBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * Private Constructors  * * * * * * * * * * * * * //

Registry::Registry(const Registry& r) noexcept
:
	owner_ {&r}
{}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename T>
auto&& Registry::obtain() const
{
	auto search {data_.find(T::name)};

	if (search == data_.end())
		if (owner_)
			return owner_->obtain<T>();

		// construct if it doesn't exist
		auto&& [iter, success] store
		(
			std::move(input::read<T>())
		);

		return *(static_cast<T*>(iter->second.get()));
	else
		return *(static_cast<T*>(search->second.get()));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Registry& Registry::create() noexcept
{
	if (!slaves_)
		slaves_->reset
		(
			std::make_unique<Ptrvector<Registry>>()
		);

	slaves_->emplace_back
	(
		std::make_unique<Registry>(*this)
	);
	return *(slaves_->back());
}


template<typename T>
const T& Registry::cref() const
{
	return this->obtain<T>();
}


template<typename T>
T Registry::get()
{
	return this->obtain<T>();
}


template<typename T, enum Registry::Scope S>
bool Registry::has() const noexcept
{
	return has<S>(T::name);
}


template<enum Registry::Scope S>
bool Registry::has(const word& key) const noexcept
{
	auto search {data_.find(key)};

	if (search == data_.end())
		// recurse for if searching globally
		if constexpr (S == Registry::GLOBAL)
			if (owner_)
				return owner_->has<S>(key);
		else
			return false;

	return true;
}


Registry* Registry::owner() const noexcept
{
	return this->owner_;
}


template<typename T>
T& Registry::ref()
{
	return this->obtain<T>();
}


template<typename T>
[[maybe_unused]] auto Registry::store(T&& t)
{
	// returns pair<iterator, bool>
	return data_.insert_or_assign
	(
		T::name,
		std::make_unique<T>(std::forward<T>(t))
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
