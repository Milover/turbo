/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::ThicknessGeneratorBase

Description
	Abstract base class for distribution generator classes

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_THICKNESS_THICKNESS_GENERATOR_BASE_H
#define DESIGN_PROFILE_THICKNESS_THICKNESS_GENERATOR_BASE_H

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class ThicknessGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class ThicknessGeneratorBase
{
protected:

	// Protected data

		input::MaxProfileThickness max_;


	// Constructors

		//- Default constructor
		ThicknessGeneratorBase() = default;


public:

	// Constructors

		//- Construct from a registry
		ThicknessGeneratorBase(const input::Registry& reg);

		//- Copy constructor
		ThicknessGeneratorBase(const ThicknessGeneratorBase&) = delete;

		//- Move constructor
		ThicknessGeneratorBase(ThicknessGeneratorBase&&) = default;


	//- Destructor
	virtual ~ThicknessGeneratorBase() = default;


	// Member functions

		//- Get thickness at 'x' (half of total thickness)
		virtual Float thickness(const Float x) const noexcept(ndebug) = 0;


	// Member operators

		//- Copy assignment operator
		ThicknessGeneratorBase& operator=
		(
			const ThicknessGeneratorBase&
		) = delete;

		//- Move assignment operator
		ThicknessGeneratorBase& operator=
		(
			ThicknessGeneratorBase&&
		) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
