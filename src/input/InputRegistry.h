/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::InputRegistry

Description
	InputRegistry class

SourceFiles
	InputRegistry.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_INPUT_REGISTRY_H
#define INPUT_INPUT_REGISTRY_H

#include <type_traits>

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class InputRegistry Declaration
\*---------------------------------------------------------------------------*/

class InputRegistry
{
private:


	// Private data

		inline static HashMap<String> data_ {};


	// Constructors

		//- Default constructor
		InputRegistry() = default;


public:

	// Constructors

		//- Disallow copy construction
		InputRegistry(const InputRegistry&) = delete;

		//- Dissallow move construction
		InputRegistry(InputRegistry&&) = delete;


	//- Destructor
	~InputRegistry() = default;


	// Member functions

		//- Check if empty
		static bool empty() noexcept;

		//- Get value for coresponding key
		static String get(const String& key);

		//- Check key exists
		static bool has(const String& key) noexcept;

		//- Store input map
		template<typename T>
		std::enable_if_t
		<
			std::is_same_v<T, Map<String>>
		 || std::is_same_v<T, HashMap<String>>, void
		>
		static store(T&& input);


	// Member operators

		//- Disallow copy assignment
		InputRegistry& operator=(const InputRegistry&) = delete;

		//- Disallow move assignment
		InputRegistry& operator=(const InputRegistry&&) = delete;

};


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
std::enable_if_t
<
	std::is_same_v<T, Map<String>>
 || std::is_same_v<T, HashMap<String>>, void
>
InputRegistry::store(T&& input)
{
	if constexpr (std::is_same_v<T, Map<String>>)
	{
		for (auto&& [key, value] : std::forward<T>(input))
			InputRegistry::data_.insert_or_assign
			(
				std::forward<decltype(key)>(key),
				std::forward<decltype(value)>(value)
			);
	}
	else
		InputRegistry::data_ = std::forward<T>(input);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
