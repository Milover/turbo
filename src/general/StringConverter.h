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

#include <stdexcept>
#include <string>
#include <type_traits>

#include "Error.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
					Class StringConverter Declaration
\*---------------------------------------------------------------------------*/

template<typename T>
class StringConverter
{
private:

	// Private data

		std::string::size_type pos_;


public:

	// Constructors

		//- Default constructor
		StringConverter() = default;

		//- Disallow copy construction
		StringConverter(const StringConverter&) = default;

		//- Move constructor
		StringConverter(StringConverter&&) = default;


	//- Destructor
	~StringConverter() = default;


	// Member operators

		//- Assignment operator
		StringConverter& operator=(const StringConverter&) = default;

		//- Perform conversion
		T static convert(const std::string& s);

		//- Function call operator
		T operator()(const std::string& s);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
T StringConverter<T>::operator()(const std::string& s)
{
	T t {convert<T>(s)};

	// we demand complete conversion,
	// partial matches are not allowed
	if (pos_ != s.size())
		THROW_ARGUMENT_ERROR("Partial match on: " + s);
	else
		return t;
}


template<>
double StringConverter<double>::convert(const std::string& s)
{
	try
	{
		return std::stod(s, &pos_);
	}
	catch(...)
	{
		THROW_ARGUMENT_ERROR("Could not perform conversion on: " + s);
	}
}


template<>
int StringConverter<int>::convert(const std::string& s)
{
	try
	{
		return std::stoi(s, &pos_);
	}
	catch(...)
	{
		THROW_ARGUMENT_ERROR("Could not perform conversion on: " + s);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
