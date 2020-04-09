/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RegistryObject

Description
	Base class template for registry objects.
	Checks if floating-point-like values (including vectors) are NaN.

	WARNING:
		Derived classes must define a static string 'name'.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_REGISTRY_OBJECT_H
#define INPUT_REGISTRY_OBJECT_H

#include <cmath>
#include <type_traits>
#include <utility>

#include "Error.h"
#include "InputRegistry.h"
#include "StringConverter.h"
#include "RegistryObjectBase.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class RegistryObject Definition
\*---------------------------------------------------------------------------*/

template<typename T>
class RegistryObject
:
	public RegistryObjectBase
{
protected:

	static_assert
	(
		std::is_arithmetic_v<T> || std::is_same_v<Vector, T>
	);

	using RegBase = typename RegistryObject<T>;


	// Protected data

		T value_;


	// Constructors

		//- Construct from input
		explicit RegistryObject(T&& t) noexcept(std::is_integral_v<T>);

		//- Check input
		virtual void check() const noexcept(std::is_integral_v<T>) override;


public:

	using type = typename T;


	// Constructors

		//- Copy constructor
		RegistryObject(const RegistryObject<T>&) = default;

		//- Move constructor
		RegistryObject(RegistryObject<T>&&) = default;


	//- Destructor
	virtual ~RegistryObject() = default;


	// Member functions

		//- Get value
		T value() const noexcept;

		//- Set value
		void set(T&& t);


	// Member operators

		//- Copy assignment operator
		RegistryObject<T>& operator=(const RegistryObject<T>&) = default;

		//- Move assignment operator
		RegistryObject<T>& operator=(RegistryObject<T>&&) = default;

};


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
RegistryObject<T>::RegistryObject(T&& t) noexcept(std::is_integral_v<T>)
:
	value_ {std::forward<T>(t)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T>
RegistryObject<T>::check()
void RegistryObject<T>::check() const noexcept(std::is_integral_v<T>)
{
	if constexpr (std::is_floating_point_v<T>)
		if (std::isnan(this->value_))
			THROW_ARGUMENT_ERROR("value is NaN");
	else if constexpr (std::is_same_v<Vector, T>)
		for (auto&& i : this->value_)
			if (std::isnan(i))
				THROW_ARGUMENT_ERROR("value is NaN");
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
T RegistryObject<T>::value() const noexcept
{
	return this->value_;
}


template<typename T>
void RegistryObject<T>::set(T&& t)
{
	this->value_ = std::forward<T>(t);
	this->check();
}


// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

//- Convert a Word into an appropriate type
//  based on the template parameter of the RegistryObject
template<typename T>
typename T::type convert(const Word& value)
{
	return StringConverter<typename T::type> {}(value);
}


//- Create a RegistryObject by reading the InputRegistry if possible
//  otherwise default construct if possible
template<typename T>
std::enable_if_t<std::is_base_of_v<RegistryObjectBase, T>, T>
read()
{
	if constexpr (std::is_default_constructible_v<T>)
		if (InputRegistry::has(T::name))
			return T
			{
				input::convert<T>
				(
					InputRegistry::get(T::name)
				)
			};
		else
			return T {};
	else
		return T
		{
			input::convert<T>
			(
				InputRegistry::get(T::name)
			)
		};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
