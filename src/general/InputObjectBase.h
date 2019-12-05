/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::InputObjectBase

Description
	Abstract base class for objects which are constructed from user input.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_OBJECT_BASE_H
#define INPUT_OBJECT_BASE_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "Error.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
						Class InputObjectBase Definition
\*---------------------------------------------------------------------------*/

template<typename T = double>
class InputObjectBase
{
protected:

	// Protected data

		Stringmap<T> inputMap_;
		std::vector<std::string> optionalKeys_;


	// Constructors

		//- Default constructor
		InputObjectBase() = default;


	// Member functions

		//- Add optional keys
		template<typename... Ts>
		void addOptional(Ts&&... ts) noexcept;

		//- Build input map
		virtual void buildInputMap() noexcept = 0;

		//- Convert value to T
		virtual T convert(const std::string& value) const = 0;

		//- Check if key is optional
		bool isOptional(const std::string& key) const noexcept;

		//- Read input
		//void read() const; 						// <- implement later

		//- Parse input
		virtual void parse(const Stringmap<>& input);

		//- Insert key and value into map or
		//  assign value to key
		void store
		(
			const std::string& key,
			const T& t
		);


public:

	// Constructors

		//- Disallow copy construction
		InputObjectBase(const InputObjectBase&) = delete;

		//- Move constructor
		InputObjectBase(InputObjectBase&&) = default;


	//- Destructor
	virtual ~InputObjectBase() = default;


	// Member functions

		//- Get value from map
		virtual T get(const std::string& key) const;

		//- Check if map contains key
		bool hasKey(const std::string& key) const noexcept;

		//- Check if value is initialized
		virtual bool hasValue(const std::string& key) const noexcept = 0;


	// Member operators

		//- Disallow assignment
		InputObjectBase& operator=(const InputObjectBase&) = delete;

};


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<typename T>
template<typename... Ts>
void InputObjectBase<T>::addOptional(Ts&&... ts) noexcept
{
	(this->optionalKeys_.push_back(ts),...);
}


template<typename T>
bool InputObjectBase<T>::isOptional(const std::string& key) const noexcept
{
	for (const auto& k : this->optionalKeys_)
		if (k == key)
			return true;

	return false;
}


template<typename T>
void InputObjectBase<T>::parse(const Stringmap<>& input)
{
	for (auto& [key, value] : this->inputMap_)
	{
		auto search {input.find(key)};

		if (search == input.end())
		{
			if (isOptional(key))
				continue;
			else
				THROW_RUNTIME_ERROR("keyword '" + key + "' undefined");
		}
		else
			value = convert(search->second);
	}
}


template<typename T>
void InputObjectBase<T>::store
(
	const std::string& key,
	const T& t
)
{
	this->inputMap_.insert_or_assign(key, t);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
T InputObjectBase<T>::get(const std::string& key) const
{
	auto search {this->inputMap_.find(key)};

	if (search == this->inputMap_.end())
		THROW_ARGUMENT_ERROR("key '" + key + "' does not exist");

	return search->second;
}


template<typename T>
bool InputObjectBase<T>::hasKey(const std::string& key) const noexcept
{
	auto search {this->inputMap_.find(key)};

	if (search == this->inputMap_.end())
		return false;

	return true;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
