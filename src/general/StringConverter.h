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

#include "Error.h"
#include "General.h"

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

		Word::size_type pos_;


public:

	using type = typename T;


	// Member functions

		//- Perform conversion
		T static convert(const Word& s);


	// Member operators

		//- Function call operator
		T operator()(const Word& s);

};


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<typename T>
T StringConverter<T>::operator()(const Word& s)
{
	T t
	{
		StringConverter<T>::convert(s)
	};

	// we demand complete conversion,
	// partial matches are not allowed
	if (this->pos_ != s.size())
		THROW_ARGUMENT_ERROR("Partial match on: " + s);
	else
		return t;
}


template<>
Float StringConverter<Float>::convert(const Word& s)
{
	try
	{
		return std::stod(s, &this->pos_);
	}
	catch(...)
	{
		THROW_ARGUMENT_ERROR("Could not perform conversion on: " + s);
	}
}


template<>
Integer StringConverter<Integer>::convert(const Word& s)
{
	try
	{
		return std::stoi(s, &this->pos_);
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
