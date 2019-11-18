/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ProfileGeneratorInterface

Description
	Interface class for other ProfileGenerator classes

SourceFiles
	ProfileGeneratorInterface.cpp

\*---------------------------------------------------------------------------*/

#ifndef PROFILE_GENERATOR_INTERFACE_H
#define PROFILE_GENERATOR_INTERFACE_H

#include "GenericInterface.h"
#include "Point.h"
#include "ProfileGeneratorBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
				Class ProfileGeneratorInterface Declaration
\*---------------------------------------------------------------------------*/

class ProfileGeneratorInterface final
:
	public GenericInterface<ProfileGeneratorBase, Stringmap>
{
protected:

	// Member functions
		
		//- Create the underlying object to interface
		void createInterfaceObject(const Stringmap& input) override;


public:
	
	// Constructors
		
		//- Construct from input data
		ProfileGeneratorInterface(const Stringmap& input);
	

	//- Destructor
	~ProfileGeneratorInterface() = default;


	// Member functions
		
		//- Get number of (camber line) points
		int getSize() const noexcept;

		//- Check if coordinates have beed generated
		bool isEmpty() const noexcept;

		//- Get a point on the upper surface at ``pos''
		Point getUpperPointAt(const int pos) const;

		//- Get a point on the lower surface at ``pos''
		Point getLowerPointAt(const int pos) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
