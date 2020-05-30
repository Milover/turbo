/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StringConverter.h"

#include "Error.h"
#include "General.h"
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
Vector StringConverter<Vector>::convert(const String& s [[maybe_unused]])
{
	Vector v;

	// the vector does all the checking
	this->stream_ >> v;

	return v;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
