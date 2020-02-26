/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::geometry::DistributionGeneratorBase

Description
	Abstract base class for distribution generator classes

\*---------------------------------------------------------------------------*/

#ifndef DISTRIBUTION_GENERATOR_BASE_H
#define DISTRIBUTION_GENERATOR_BASE_H

#include <string>

#include "InputObjectBase.h"
#include "Utility.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace geometry
{

/*---------------------------------------------------------------------------*\
					Class DistributionGeneratorBase Declaration
\*---------------------------------------------------------------------------*/

class DistributionGeneratorBase
:
	public InputObjectBase<double>
{
protected:

	// Constructors

		//- Default constructor
		DistributionGeneratorBase() = default;


	// Member functions

		//- Check input
		virtual void check() const = 0;

		//- Convert value to double
		double convert(const std::string& value) const final;


public:

	// Constructors

		//- Move constructor
		DistributionGeneratorBase(DistributionGeneratorBase&&) = default;


	//- Destructor
	virtual ~DistributionGeneratorBase() = default;


	// Member functions

		//- Get thickness at ``x'' (half of total thickness)
		virtual double getThicknessAt(const double x) const noexcept = 0;

		//- Check if value is initialized
		bool hasValue(const std::string& key) const noexcept final;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geometry
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
