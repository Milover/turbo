/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StringConverter.h"

#include "Error.h"
#include "General.h"
#include "List.h"
#include "Vector.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<>
Float StringConverter<Float>::convert(const String& s)
{
	Float f;

	this->stream_ >> f;

	this->check(s);

	return f;
}


template<>
Integer StringConverter<Integer>::convert(const String& s)
{
	Integer i;

	this->stream_ >> i;

	this->check(s);

	return i;
}


template<>
std::size_t StringConverter<std::size_t>::convert(const String& s)
{
	std::size_t i;

	this->stream_ >> i;

	this->check(s);

	return i;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
