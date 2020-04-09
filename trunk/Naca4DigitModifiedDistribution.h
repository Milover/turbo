/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::Naca4DigitModifiedDistribution

Description
	Class Naca4DigitModifiedDistribution
	For more information on the generation procedure see \cite{}.

	Note that the ``radiusIndex'' and ``maxThicknessPostion'' may be
	floating point values.

SourceFiles
	Naca4DigitModifiedDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef NACA_4_DIGIT_MODIFIED_H
#define NACA_4_DIGIT_MODIFIED_H

#include <array>
#include <map>

#include "DistributionGeneratorBase.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
			Class Naca4DigitModifiedDistribution Declaration
\*---------------------------------------------------------------------------*/

class Naca4DigitModifiedDistribution final
:
	public DistributionGeneratorBase
{
private:

	// Private data

		std::array<double, 4> a_;
		std::array<double, 4> d_;

		const double chord_ {1.0};
		const double scale_ {5.0};
		const std::map<int, double> d1Table_
		{
			{2, 0.200},
			{3, 0.234},
			{4, 0.315},
			{5, 0.465},
			{6, 0.700}
		};


	// Member functions

		//- Check max thickness position
		void checkMaxThickness() const;

		//- Check max thickness position
		void checkMaxThicknessPosition() const;

		//- Check radius index
		void checkRadiusIndex() const;

		//- Compute $a_0$ coefficient
		void computeA0() noexcept;

		//- Look up $d_1$ coefficient
		void lookUpD1() noexcept;

		//- Compute $d_2$ coefficient
		void computeD2() noexcept;

		//- Compute $d_3$ coefficient
		void computeD3() noexcept;

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
		Naca4DigitModifiedDistribution(const Stringmap<>& input);

		//- Move constructor
		Naca4DigitModifiedDistribution
		(
			Naca4DigitModifiedDistribution&&
		) = default;


	//- Destructor
	~Naca4DigitModifiedDistribution() = default;


	// Member functions

		//- Get thickness at ``x'' (half of total thickness)
		double getThicknessAt(const double x) const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
