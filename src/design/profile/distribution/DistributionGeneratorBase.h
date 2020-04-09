/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::DistributionGeneratorBase

Description
	Abstract base class for distribution generator classes

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_DISTRIBUTION_GENERATOR_BASE_H
#define DESIGN_DISTRIBUTION_GENERATOR_BASE_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class DistributionGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class DistributionGeneratorBase
{
protected:

	// Constructors

		//- Default constructor
		DistributionGeneratorBase() = default;


public:

	// Constructors

		//- Copy constructor
		DistributionGeneratorBase(const DistributionGeneratorBase&&) = default;

		//- Move constructor
		DistributionGeneratorBase(DistributionGeneratorBase&&) = default;


	//- Destructor
	virtual ~DistributionGeneratorBase() = default;


	// Member functions

		//- Get thickness at 'x' (half of total thickness)
		virtual Float thickness(const Float x) const noexcept = 0;
			// FIXME: we should probably check range here [0, 1]


	// Member operators

		//- Copy assignment operator
		DistributionGeneratorBase& operator=
		(
			const DistributionGeneratorBase&&
		) = default;

		//- Move assignment operator
		DistributionGeneratorBase& operator=
		(
			DistributionGeneratorBase&&
		) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
