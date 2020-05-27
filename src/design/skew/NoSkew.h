/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::NoSkew

Description
	Class NoSkew

SourceFiles
	NoSkew.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_SKEW_NO_SKEW_H
#define DESIGN_SKEW_NO_SKEW_H

#include "Error.h"
#include "General.h"
#include "SkewDistributionBase.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class NoSkew Declaration
\*---------------------------------------------------------------------------*/

class NoSkew final
:
	public SkewDistributionBase
{
public:

	// Public data

		inline static const String name {"NoSkew"};


	// Constructors

		//- Defaul constructor
		NoSkew() = default;


	// Member functions

		//- Apply skew to profile
		void skew(Profile& profile) const noexcept override;


};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
