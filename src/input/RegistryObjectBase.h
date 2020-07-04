/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RegistryObjectBase

Description
	Abstract base class for registry objects.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_REGISTRY_OBJECT_BASE_H
#define INPUT_REGISTRY_OBJECT_BASE_H

#include <ostream>

#include "Error.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class RegistryObjectBase Declaration
\*---------------------------------------------------------------------------*/

class RegistryObjectBase
{
protected:

	// Constructors

		//- Default constructor
		RegistryObjectBase() = default;


	// Member functions

		//- Check input
		virtual void check() const noexcept(ndebug) = 0;


public:

	// Constructors

		//- Copy constructor
		RegistryObjectBase(const RegistryObjectBase&) = default;

		//- Move constructor
		RegistryObjectBase(RegistryObjectBase&&) = default;


	//- Destructor
	virtual ~RegistryObjectBase() = default;

	// Member functions

		//- Get object name
		virtual String getName() const = 0;

		//- Print formated output ('name[delimiter]value[terminator]'),
		//	optionally set the delimiter, terminator and
		//	total output field width (pads with whitespace)
		virtual void print
		(
			std::ostream& os,
			const String::size_type width = 0,
			const String& delimiter = " ",
			const String& terminator = ";",
			const Integer precision = 9
		) const = 0;


	// Member operators

		//- Copy assignment operator
		RegistryObjectBase& operator=(const RegistryObjectBase&) = default;

		//- Move assignment operator
		RegistryObjectBase& operator=(RegistryObjectBase&&) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
