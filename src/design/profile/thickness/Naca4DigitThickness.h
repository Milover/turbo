/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Naca4DigitThickness

Description
	Class Naca4DigitThickness
	For more information on the generation procedure see \cite{}.

SourceFiles
	Naca4DigitThickness.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_PROFILE_THICKNESS_NACA_4_DIGIT_THICKNESS_H
#define DESIGN_PROFILE_THICKNESS_NACA_4_DIGIT_THICKNESS_H

#include <array>

#include "ThicknessGeneratorBase.h"
#include "Error.h"
#include "General.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
				Class Naca4DigitThickness Declaration
\*---------------------------------------------------------------------------*/

class Naca4DigitThickness final
:
	public ThicknessGeneratorBase
{
private:

	// Private data

		static constexpr Float scale_ {5.0};
		std::array<Float, 5> a_
		{
			0.2969,
		   -0.1260,
		   -0.3516,
			0.2843,
		   -0.1015
		};


public:

	// Public data

		inline static const String name {"Naca4DigitThickness"};


	// Constructors

		//- Default constructor
		Naca4DigitThickness(const input::Registry& reg);


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
