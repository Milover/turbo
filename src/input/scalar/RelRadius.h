/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::RelRadius

Description
	Class RelRadius.

	Defined as:

	/[
		(r - r_h) / (r_s - z_tip - r_h)
	/]

SourceFiles
	RelRadius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_REL_RADIUS_H
#define INPUT_REL_RADIUS_H

#include "General.h"
#include "HubRadius.h"
#include "LimitedValue.h"
#include "Radius.h"
#include "ShroudRadius.h"
#include "TipClearance.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class RelRadius Declaration
\*---------------------------------------------------------------------------*/

class RelRadius final
:
	public LimitedValue<Float, 0, 1>
{
public:

	// Public static data

		inline static const String name {"RelRadius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit RelRadius(const Float f);

		//- Compute and construct
		RelRadius
		(
			const Radius& r,
			const HubRadius& r_h,
			const ShroudRadius& r_s,
			const TipClearance& z_tip
		);


	// Member functions

		//- Get object name
		String getName() const override;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
