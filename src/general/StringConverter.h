/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::StringConverter

Description
	A simple class for string conversion

\*---------------------------------------------------------------------------*/

#ifndef STRING_CONVERTER_H
#define STRING_CONVERTER_H

#include <type_traits>
#include <sstream>

#include "Error.h"
#include "General.h"
#include "List.h"
#include "Polyline.h"
#include "Utility.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * * * Global Helpers  * * * * * * * * * * * * * * * //

//- A type trait for types convertible from String
template<typename T>
struct isConvertible : std::false_type {};


//- An ease of use variable alias template
template<typename T>
inline constexpr bool isConvertible_v = isConvertible<T>::value;


// We know how to convert from String to Integer
template<>
struct isConvertible<Integer> : std::true_type {};


// We know how to convert from String to std::size_t
template<>
struct isConvertible<std::size_t> : std::true_type {};


// We know how to convert from String to Float
template<>
struct isConvertible<Float> : std::true_type {};


// We know how to convert from String to List of T
template<typename U>
struct isConvertible<List<U>> : std::bool_constant<isConvertible_v<U>> {};


// We know how to convert from String to Polyline of T
template<typename U>
struct isConvertible<math::Polyline<U>>
:
	std::bool_constant<isConvertible_v<U>>
{};


// We know how to convert from String to Vector
template<>
struct isConvertible<Vector> : std::true_type {};


/*---------------------------------------------------------------------------*\
					Class StringConverter Declaration
\*---------------------------------------------------------------------------*/

template<typename T>
class StringConverter
{
private:

	static_assert(isConvertible_v<T>);


	// Private data

		std::stringstream stream_;


	// Member functions

		//- Perform conversion
		T convert(const String& s);

		//- Check if conversion was successful
		void check(const String& s) const noexcept(ndebug);


public:

	using type = T;


	// Member operators

		//- Function call operator
		T operator()(const String& s);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
T StringConverter<T>::operator()(const String& s)
{
	String str {s};

	// trim leading and trailing whitespace
	trimWhiteLR(str);

	// reset the stream and read in the string
	this->stream_ = std::stringstream {};
	this->stream_ << str;

	// need 's' to print out where the error occured
	return this->convert(s);
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename T>
void StringConverter<T>::check(const String& s) const noexcept(ndebug)
{
	if (stream_.fail())
		error(FUNC_INFO, "Could not perform conversion on: ", s);
	else if (!stream_.eof())
		error(FUNC_INFO, "Partial match: ", s);
}


template<typename T>
T StringConverter<T>::convert(const String& s [[maybe_unused]])
{
	// this is our generic, one-size-fits-all implementation,
	// some specializations are in the source file
	T t;

	this->stream_ >> t;

	return t;
}


// * * * * * * * * * * * * * * Specializations * * * * * * * * * * * * * * * //

template<>
Float StringConverter<Float>::convert(const String& s);

template<>
Integer StringConverter<Integer>::convert(const String& s);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
