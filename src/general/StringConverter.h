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


// We know how to convert from String to Float
template<>
struct isConvertible<Float> : std::true_type {};


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
		void check(const String& s) const;


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
	return T {this->convert(s)};
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<typename T>
void StringConverter<T>::check(const String& s) const
{
	if (stream_.fail())
		THROW_RUNTIME_ERROR("Could not perform conversion on: " + s);
	else if (!stream_.eof())
		THROW_RUNTIME_ERROR("Partial match: " + s);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
