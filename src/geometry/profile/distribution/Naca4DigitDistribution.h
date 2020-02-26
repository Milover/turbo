/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::Naca4DigitDistribution

Description
	Class Naca4DigitDistribution
	For more information on the generation procedure see \cite{}.

SourceFiles
	Naca4DigitDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef NACA_4_DIGIT_DISTRIBUTION_H
#define NACA_4_DIGIT_DISTRIBUTION_H

#include <array>

#include "DistributionGeneratorBase.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
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

		std::array<double, 5> a_;

		const double scale_ {5.0};


	// Member functions

		//- Scale coefficients
		void scaleCoefficients();


protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check input
		void check() const override;


public:

	// Constructors

		//- Default constructor
		Naca4DigitDistribution(const Stringmap<>& input);

		//- Move constructor
		Naca4DigitDistribution
		(
			Naca4DigitDistribution&&
		) = default;


	//- Destructor
	~Naca4DigitDistribution() = default;


	// Member functions

		//- Get thickness at ``x'' (half of total thickness)
		double getThicknessAt(const double x) const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
