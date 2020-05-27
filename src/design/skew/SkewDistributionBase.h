/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::SkewDistributionBase

Description
	Abstract base class for skew distribution classes

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_SKEW_SKEW_DISTRIBUTION_BASE_H
#define DESIGN_SKEW_SKEW_DISTRIBUTION_BASE_H

#include "General.h"
#include "Profile.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class SkewDistributionBase Declaration
\*---------------------------------------------------------------------------*/

class SkewDistributionBase
{
protected:

	// Constructors

		//- Default constructor
		SkewDistributionBase() = default;


public:

	// Constructors

		//- Copy constructor
		SkewDistributionBase(const SkewDistributionBase&) = delete;

		//- Move constructor
		SkewDistributionBase(SkewDistributionBase&&) = default;


	//- Destructor
	virtual ~SkewDistributionBase() = default;


	// Member functions

		//- Apply skew to a profile
		virtual void skew(Profile& profile) const = 0;


	// Member operators

		//- Copy assignment operator
		SkewDistributionBase& operator=(const SkewDistributionBase&) = delete;

		//- Move assignment operator
		SkewDistributionBase& operator=(SkewDistributionBase&&) = default;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
