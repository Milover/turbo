/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::ConstantThickness

Description
	Class ConstantThickness

SourceFiles
	ConstantThickness.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_THICKNESS_CONSTANT_THICKNESS_H
#define DESIGN_PROFILE_THICKNESS_CONSTANT_THICKNESS_H

#include "Error.h"
#include "General.h"
#include "Registry.h"
#include "ThicknessGeneratorBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
				Class ConstantThickness Declaration
\*---------------------------------------------------------------------------*/

class ConstantThickness final
:
	public ThicknessGeneratorBase
{
public:

	// Public data

		inline static const String name {"ConstantThickness"};


	// Constructors

		//- Defaul constructor
		ConstantThickness(const input::Registry& reg);


	// Member functions

		//- Get thickness at 'x' (half of total thickness)
		Float thickness(const Float x) const noexcept(ndebug) override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
