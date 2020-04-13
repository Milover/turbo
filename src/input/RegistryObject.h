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
		Derived classes must define a static string 'name' which
		must be identical to the class name.

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
		std::is_arithmetic_v<T>
	 || std::is_enum_v<T>
	 || std::is_same_v<Vector, T>
	);

	using RegBase = RegistryObject<T>;


	// Protected data

		T value_;


	// Constructors

		//- Construct from input
		template
		<
			typename U,
			std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int> = 0
		>
		explicit RegistryObject(U&& u) noexcept(std::is_integral_v<T>);

		//- Check input
		virtual void check() const override;


public:

	using type = T;


	// Constructors

		//- Copy constructor
		RegistryObject(const RegistryObject&) = default;

		//- Move constructor
		RegistryObject(RegistryObject&&) = default;


	//- Destructor
	virtual ~RegistryObject() = default;


	// Member functions

		//- Get value
		inline T value() const noexcept;

		//- Set value
		template
		<
			typename U,
			std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int> = 0
		>
		void set(U&& u);


	// Member operators

		//- Copy assignment operator
		RegistryObject& operator=(const RegistryObject&) = default;

		//- Move assignment operator
		RegistryObject& operator=(RegistryObject&&) = default;

};


// * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * * //

//- Convert a String into an appropriate type
//  based on the template parameter of the RegistryObject
template<typename T>
typename T::type convert(const String& value)
{
	return StringConverter<typename T::type> {}(value);
}


//- Create a RegistryObject by reading the InputRegistry if possible
//  otherwise default construct if possible
template<typename T>
std::enable_if_t<std::is_base_of_v<RegistryObjectBase, T>, T>
read()
{
	// read if special construction is implemented locally
	if constexpr (std::is_constructible_v<T, String>)
		if (InputRegistry::has(T::name))
			return T
			{
				InputRegistry::get(T::name)
			};

	// read-convert only if we know how to convert
	if constexpr (isConvertible_v<typename T::type>)
		if (InputRegistry::has(T::name))
			return T
			{
				input::convert<T>
				(
					InputRegistry::get(T::name)
				)
			};

	// if we can't read, maybe we can default-construct
	if constexpr (std::is_default_constructible_v<T>)
		return T {};

	if constexpr (isConvertible_v<typename T::type>)
		THROW_ARGUMENT_ERROR(T::name + " undefined");
	else
	{
		THROW_ARGUMENT_ERROR("conversion for '" + T::name + "' unimplemented");
		__builtin_unreachable();
	}
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
template
<
	typename U,
	std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int>
>
RegistryObject<T>::RegistryObject(U&& u) noexcept(std::is_integral_v<T>)
:
	value_ {std::forward<U>(u)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T>
void RegistryObject<T>::check() const
{
	if constexpr (std::is_floating_point_v<T>)
	{
		if (std::isnan(this->value_))
			THROW_ARGUMENT_ERROR("value is NaN");
	}
	else if constexpr (std::is_same_v<Vector, T>)
	{
		if (isNan(this->value_))
			THROW_ARGUMENT_ERROR("value is NaN");
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
T RegistryObject<T>::value() const noexcept
{
	return this->value_;
}


template<typename T>
template
<
	typename U,
	std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>, int>
>
void RegistryObject<T>::set(U&& u)
{
	this->value_ = std::forward<U>(u);
	this->check();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
