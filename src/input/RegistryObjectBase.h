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
		virtual void check() const = 0;


public:

	// Constructors

		//- Copy constructor
		RegistryObjectBase(const RegistryObjectBase&) = default;

		//- Move constructor
		RegistryObjectBase(RegistryObjectBase&&) = default;


	//- Destructor
	virtual ~RegistryObjectBase() = default;


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
