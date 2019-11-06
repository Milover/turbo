/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::GenericInterface

Description
	Abstract base class template for interface classes

\*---------------------------------------------------------------------------*/

#ifndef GENERIC_INTERFACE_H
#define GENERIC_INTERFACE_H

#include <memory>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{

/*---------------------------------------------------------------------------*\
					Class GenericInterface Declaration
\*---------------------------------------------------------------------------*/

template<class U, class V>
class GenericInterface
{
protected:

	// Protected data
		
		std::unique_ptr<U> interfaceObject_;


	// Constructors
		
		//- Default constructor
		GenericInterface() = default;


	// Member functions
		
		//- Create underlying object to interface
		virtual void createInterfaceObject(const V&) = 0;


public:
	
	// Constructors
		
		//- Disallow copy construction
		GenericInterface(const GenericInterface&) = delete;


	//- Destructor
	virtual ~GenericInterface() = default;


	// Member operators

		//- Disallow assignment
		GenericInterface& operator=(const GenericInterface&) = delete;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
