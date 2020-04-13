/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::VortexDistributionExponent

Description
	Class VortexDistributionExponent.
	Limited to [-1, 1], where

	   -1 - free vortex distribution
		0 - const. vortex distribution
		1 - forced vortex distribution
	
	Defaults to -1 (free vortex distribution).

SourceFiles
	VortexDistributionExponent.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VORTEX_DISTRIBUTION_EXPONENT_H
#define INPUT_VORTEX_DISTRIBUTION_EXPONENT_H

#include "General.h"
#include "LimitedValue.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
				Class VortexDistributionExponent Declaration
\*---------------------------------------------------------------------------*/

class VortexDistributionExponent final
:
	public LimitedValue<Float, -1, 1>
{
public:

	// Public static data

		inline static const String name {"VortexDistributionExponent"};


	// Constructors

		//- Default constructor
		VortexDistributionExponent() noexcept;

		//- Construct from a Float,
		//  no aditional checking required
		explicit VortexDistributionExponent(const Float f);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
