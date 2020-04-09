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

#include <type_traits>

#include "General.h"
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

	// Private data

		Registry* owner_ {nullptr};
		Uptr<Ptrvector<Registry>> slaves_ {nullptr};
			// NOTE: currently grows infinitely i.e.
			// 		 no removal of slaves (only removed once owner destructs
			// 		 and no resize after removal of a slave)
			// 		 should we manage this?

		HashMap<Uptr<RegistryObjectBase>> data_;


	// Constructors

		//- Default construct and set owner
		Registry(const Registry&) noexcept;


	// Member functions

		//- Recursively get a registry object (value, ref or cref)
		//  i.e. search through global scope.
		//  If a registry object doesn't exist
		//  do a 'read()' (if possible) and store locally
		template<typename T, enum Registry::Scope S = Registry::GLOBAL>
		auto&& obtain() const;


public:

	enum Scope
	{
		LOCAL,
		GLOBAL
	};


	// Constructors

		//- Default constructor
		Registry() = default;

		//- Dissallow move constructor
		Registry(Registry&&) = delete;


	//- Destructor
	~Registry() = default;


	// Member functions

		//- Create a new (slave) registry
		Registry& create() noexcept;

		//- Recursively get a const reference to a registry object
		template<typename T>
		const T& cref() const;

		//- Recursively get a registry object
		template<typename T, enum Registry::Scope S = Registry::GLOBAL>
		T get() const;

		//- Check if a registry object exists (locally or globally)
		template<typename T, enum Registry::Scope S = Registry::GLOBAL>
		bool has() const noexcept;

		//- Check if a registry object (key) exists (locally or globally)
		template<enum Registry::Scope S = Registry::GLOBAL>
		bool has(const Word& key) const noexcept;

		//- Get owner
		Registry* owner() const noexcept;

		//- Recursively get a reference to a registry object
		template<typename T>
		T& ref();

		//- Store (insert or assign) a registry object (locally)
		template<typename T>
		[[maybe_unused]] auto store(T&& t);


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
	if constexpr (sizeof...(Ts) == 0)
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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
