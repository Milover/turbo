/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::NoCamber

Description
	Class NoCamber declaration.

	Generates a straight camber line, i.e. the profile will be uncambered.
	Used mostly for testing purposes.

SourceFiles
	NoCamber.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_NO_CAMBER_H
#define DESIGN_NO_CAMBER_H

#include "CamberGeneratorBase.h"
#include "Error.h"
#include "Registry.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class NoCamber Declaration
\*---------------------------------------------------------------------------*/

class NoCamber final
:
	public CamberGeneratorBase
{
protected:

	// Member functions

		//- Compute camber ordinate at a 'x'
		Float computeY(const Float x) const noexcept override;


public:

	// Public data

		inline static const String name {"NoCamber"};


	// Constructors

		//- Construct from a registry
		explicit NoCamber(const input::Registry& reg);


	// Member functions

		//- Get inlination angle at 'x' in radians
		Float inclination(const Float x) const noexcept(ndebug) override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
