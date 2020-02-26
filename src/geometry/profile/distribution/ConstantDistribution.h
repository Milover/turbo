/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::ConstantDistribution

Description
	Class ConstantDistribution

SourceFiles
	ConstantDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef CONSTANT_DISTRIBUTION_H
#define CONSTANT_DISTRIBUTION_H

#include "DistributionGeneratorBase.h"
#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
				Class ConstantDistribution Declaration
\*---------------------------------------------------------------------------*/

class ConstantDistribution final
:
	public DistributionGeneratorBase
{
protected:

	// Member functions

		//- Build input map
		void buildInputMap() noexcept override;

		//- Check input
		void check() const override;


public:

	// Constructors

		//- Default constructor
		ConstantDistribution(const Stringmap<>& input);

		//- Move constructor
		ConstantDistribution(ConstantDistribution&&) = default;


	//- Destructor
	~ConstantDistribution() = default;


	// Member functions

		//- Get thickness at ``x'' (half of total thickness)
		double getThicknessAt(const double) const noexcept override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
