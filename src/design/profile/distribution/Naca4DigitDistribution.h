/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Naca4DigitDistribution

Description
	Class Naca4DigitDistribution
	For more information on the generation procedure see \cite{}.

SourceFiles
	Naca4DigitDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_NACA_4_DIGIT_DISTRIBUTION_H
#define DESIGN_NACA_4_DIGIT_DISTRIBUTION_H

#include <array>

#include "DistributionGeneratorBase.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
				Class Naca4DigitDistribution Declaration
\*---------------------------------------------------------------------------*/

class Naca4DigitDistribution final
:
	public DistributionGeneratorBase
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

		Float maxThickness_;

public:

	// Constructors

		//- Default constructor
		Naca4DigitDistribution();


	// Member functions

		//- Get thickness at 'x' (half of total thickness)
		Float thickness(const Float x) const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
