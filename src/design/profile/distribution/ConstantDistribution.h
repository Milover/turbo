/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::ConstantDistribution

Description
	Class ConstantDistribution

SourceFiles
	ConstantDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_CONSTANT_DISTRIBUTION_H
#define DESIGN_CONSTANT_DISTRIBUTION_H

#include "DistributionGeneratorBase.h"
#include "Error.h"
#include "General.h"
#include "Variables.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
				Class ConstantDistribution Declaration
\*---------------------------------------------------------------------------*/

class ConstantDistribution final
:
	public DistributionGeneratorBase
{
private:

	// Private data

		input::MaxProfileThickness max_;


public:

	// Private data

		inline static const String name {"ConstantDistribution"};


	// Constructors

		//- Defaul constructor
		ConstantDistribution();


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
