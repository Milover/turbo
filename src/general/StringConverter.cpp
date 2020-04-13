/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "StringConverter.h"

#include "General.h"

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
Vector StringConverter<Vector>::convert(const String& s)
{
	double x, y, z;

	this->stream_ >> x >> y >> z;

	this->check(s);

	return Vector {x, y, z};
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// ************************************************************************* //
