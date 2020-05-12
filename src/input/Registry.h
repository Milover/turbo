/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Registry

Description
	Registry class

SourceFiles
	Registry.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_REGISTRY_H
#define INPUT_REGISTRY_H

#include <functional>
#include <ostream>
#include <utility>
#include <type_traits>

#include "General.h"
#include "RegistryObject.h"
#include "RegistryObjectBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Registry Declaration
\*---------------------------------------------------------------------------*/

class Registry
{
private:

	template<typename T>
	using enableIfRecursion_t = std::enable_if_t
	<
		std::is_base_of_v<RecursionFlag, T>
	>;

	using Data = HashMap<Uptr<RegistryObjectBase>>;


	// Private data

		Registry* owner_ {nullptr};
		Uptr<Uptrvector<Registry>> slaves_ {nullptr};
			// NOTE: currently grows infinitely i.e.
			// 		 no removal of slaves (only removed once owner destructs
			// 		 and no resize after removal of a slave)
			// 		 should we manage this?

		Uptr<Data> data_;


	// Constructors

		//- Default construct and set owner
		Registry(const Registry&);


	// Member functions

		//- Get a registry object pointer (recursively or
		//	non-recursively) if the object exists,
		//	return a nullptr otherwise.
		//	TODO: try to get rid of the raw pointer
		template
		<
			typename T,
			typename R,
			typename = enableIfRecursion_t<R>
		>
		T* obtainStored() const;

		//- Get a registry object by ref/cref/value
		//	(recursively or non-recursively).
		//	If a registry object doesn't yet exist
		//	do a 'read()' (if possible) and store locally
		//  and return it by ref/cref/value.
		template
		<
			typename T,
			typename R,
			typename = enableIfRecursion_t<R>
		>
		auto&& obtain() const;


public:

	// Constructors

		//- Default constructor
		Registry();

		//- Dissallow move constructor
		Registry(Registry&&) = delete;


	//- Destructor
	~Registry() = default;


	// Member functions

		//- Create a new (slave) registry
		Registry& create();

		//- Recursively get a const reference to a registry object
		template
		<
			typename T,
			typename R = Recurse,
			typename = enableIfRecursion_t<R>
		>
		[[nodiscard]] const T& cref() const;

		//- Recursively get a registry object
		template
		<
			typename T,
			typename R = Recurse,
			typename = enableIfRecursion_t<R>
		>
		[[nodiscard]] T get() const;

		//- Check if a registry object exists (locally or globally)
		template
		<
			typename T,
			typename R = Recurse,
			typename = enableIfRecursion_t<R>
		>
		[[nodiscard]] bool has() const;

		//- Check if a registry object (key) exists (locally or globally)
		template
		<
			typename R = Recurse,
			typename = enableIfRecursion_t<R>
		>
		[[nodiscard]] bool has(const String& key) const;

		//- Get owner
		[[nodiscard]] Registry* owner() const noexcept;

		//- Recursively get a reference to a registry object
		template
		<
			typename T,
			typename R = Recurse,
			typename = enableIfRecursion_t<R>
		>
		[[nodiscard]] T& ref();

		//- Store (insert or assign) a registry object (locally)
		template<typename T>
		[[maybe_unused]] Pair<Data::iterator, bool> store(T&& t) const;

		//- Print all stored data (formatted)
		void printAll
		(
			std::ostream& os,
			const String::size_type width = 0,
			const String& delimiter = " ",
			const String& terminator = ";"
		) const;


	// Member operators

		//- Disallow copy assignment
		Registry& operator=(const Registry&) = delete;

		//- Dissallow move assignment
		Registry& operator=(Registry&&) = delete;

};


// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

//- Store a set of values into a container
template<typename Container, typename T, typename... Ts>
void storeAll(Container&& c, T&& t, Ts&&... ts)
{
	if constexpr (sizeof...(Ts) != 0)
		storeAll
		(
			std::forward<Container>(c),
			std::forward<Ts>(ts)...
		);

	if constexpr (std::is_pointer_v<Container>)
		c->store(std::forward<T>(t));
	else
		c.store(std::forward<T>(t));
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename T, typename R, typename>
T* Registry::obtainStored() const
{
	auto search {data_->find(T::name)};

	// return if found
	if (search != data_->end())
		return static_cast<T*>(search->second.get());

	// ask owner if recursing
	if constexpr (std::is_same_v<Recurse, R>)
		if (owner_)
			return owner_->obtainStored<T, R>();

	return nullptr;
}


template<typename T, typename R, typename>
auto&& Registry::obtain() const
{
	// get if someone has it already
	T* t {obtainStored<T, R>()};

	if (t)
		return *t;

	// try to construct and store from input otherwise
	auto [iter, success]
	{
		store(input::read<T>())
	};

	return *(static_cast<T*>(iter->second.get()));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T, typename R, typename>
const T& Registry::cref() const
{
	return this->obtain<T, R>();
}


template<typename T, typename R, typename>
T Registry::get() const
{
	return this->obtain<T, R>();
}


template<typename T, typename R, typename>
bool Registry::has() const
{
	return has<R>(T::name);
}


template<typename R, typename>
bool Registry::has(const String& key) const
{
	auto search {data_->find(key)};

	if (search != data_->end())
		return true;

	if constexpr (std::is_same_v<R, Recurse>)
	{
		// recurse if possible
		if (owner_)
			return owner_->has<R>(key);
		else
			return false;
	}
	else
		return false;
}


template<typename T, typename R, typename>
T& Registry::ref()
{
	return this->obtain<T, R>();
}


template<typename T>
[[maybe_unused]] Pair<Registry::Data::iterator, bool>
Registry::store(T&& t) const
{
	return data_->insert_or_assign
	(
		removeCVRef_t<T>::name,
		std::make_unique<removeCVRef_t<T>>(std::forward<T>(t))
	);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
