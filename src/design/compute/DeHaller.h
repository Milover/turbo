/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::design::DeHaller

Description
	Class DeHaller

SourceFiles
	DeHaller.cpp

\*---------------------------------------------------------------------------*/

#ifndef DESIGN_DEHALLER_H
#define DESIGN_DEHALLER_H

#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace design
{

/*---------------------------------------------------------------------------*\
						Class DeHaller Declaration
\*---------------------------------------------------------------------------*/

class DeHaller
{
public:

	// Public data

		inline static constexpr double constant {0.72};

	// Member operators

		//- Function call operator
		//  returns modified fluid outlet angle in degrees
		double operator()
		(
			const double fluidInletAngle,
			const double fluidOutletAngle
		) const noexcept;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace design
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
