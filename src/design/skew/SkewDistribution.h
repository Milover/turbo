/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::SkewDistribution

Description
	Class SkewDistribution

SourceFiles
	SkewDistribution.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_SKEW_SKEW_DISTRIBUTION_H
#define DESIGN_SKEW_SKEW_DISTRIBUTION_H

#include "SkewDistributionBase.h"
#include "Error.h"
#include "General.h"
#include "Profile.h"
#include "Registry.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
					Class SkewDistribution Declaration
\*---------------------------------------------------------------------------*/

class SkewDistribution
{
private:

	// Private data

		Uptr<SkewDistributionBase> distr_;


	// Member functions

		//- Set camber type
		void createSkewDistribution(const input::Registry& reg);


public:

	// Constructors

		//- Construct from a registry
		explicit SkewDistribution(const input::Registry& reg);


	// Member functions

		//- Apply skew to profile
		void skew(Profile& profile) const;

		//- Reset
		void reset(const input::Registry& reg);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
