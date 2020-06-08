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
#include <iomanip>
#include <ostream>
#include <sstream>
#include <type_traits>
#include <utility>

#include "Error.h"
#include "InputRegistry.h"
#include "StringConverter.h"
#include "Polyline.h"
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
	 || math::isPolyline_v<T>
	);

	using RegBase = RegistryObject<T>;


	// Protected data

		T value_;


	// Constructors

		//- Construct from input
		template
		<
			typename U,
			typename = std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>>
		>
		explicit RegistryObject(U&& u) noexcept(ndebug);

		//- Check input
		virtual void check() const noexcept(ndebug) override;


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

		//- Print formated output ('name[delimiter]value[terminator]'),
		//	optionally set the delimiter, terminator and
		//	total output field width (pads with whitespace)
		void print
		(
			std::ostream& os,
			const String::size_type width = 0,
			const String& delimiter = " ",
			const String& terminator = ";\n"
		) const override;

		//- Set value
		template
		<
			typename U,
			typename = std::enable_if_t<std::is_same_v<T, removeCVRef_t<U>>>
		>
		void set(U&& u) noexcept(ndebug);

		//- Get value
		T value() const noexcept;


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
std::enable_if_t<std::is_base_of_v<RegistryObjectBase, removeCVRef_t<T>>, T>
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
		error(FUNC_INFO, T::name, " undefined");
	else
	{
		error(FUNC_INFO, "conversion for '", T::name, "' unimplemented");
		__builtin_unreachable();
	}
}


// * * * * * * * * * * * * * Protected Constructors  * * * * * * * * * * * * //

template<typename T>
template<typename U, typename>
RegistryObject<T>::RegistryObject(U&& u) noexcept(ndebug)
:
	value_ {std::forward<U>(u)}
{
	this->check();
}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<typename T>
void RegistryObject<T>::check() const noexcept(ndebug)
{
	// XXX: why don't we check integral values?
	//if constexpr (std::is_floating_point_v<T>)
	if constexpr (std::is_arithmetic_v<T>)
	{
		if (std::isnan(this->value_))
			error(FUNC_INFO, "value of is NaN");
	}
	else if constexpr
	(
		std::is_same_v<Vector, T>
	 || math::isPolyline_v<T>
	)
	{
		if (isNan(this->value_))
			error(FUNC_INFO, "value is NaN");
	}
	else if constexpr (!std::is_enum_v<T>)
	{
		error(FUNC_INFO, "value type check not implemented");
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<typename T>
void RegistryObject<T>::print
(
	std::ostream& os,
	const String::size_type width,
	const String& delimiter,
	const String& terminator
) const
{
	std::stringstream ss;
	if constexpr (std::is_enum_v<T>)
	{
		ss << static_cast<std::underlying_type_t<T>>(this->value());
	}
	else
		ss << this->value();

	auto padding
	{
		width
	  - this->getName().size()
	  - delimiter.size()
	  + ss.str().size()
	  + terminator.size()
	};

	os << this->getName()
	   << delimiter
	   << std::setw(padding)
	   << ss.str()
	   << terminator;
}


template<typename T>
template<typename U, typename>
void RegistryObject<T>::set(U&& u) noexcept(ndebug)
{
	this->value_ = std::forward<U>(u);
	this->check();
}


template<typename T>
T RegistryObject<T>::value() const noexcept
{
	return this->value_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
