/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::Radius

Description
	Class Radius.

SourceFiles
	Radius.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_RADIUS_H
#define INPUT_RADIUS_H

#include "General.h"
#include "HubRadius.h"
#include "NumberOfStations.h"
#include "PositiveValue.h"
#include "ShroudRadius.h"
#include "TipClearance.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class Radius Declaration
\*---------------------------------------------------------------------------*/

class Radius final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"Radius"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit Radius(const Float f);

		//- Compute and construct
		Radius
		(
			const Integer i_s,				// station number (0, 1, 2...)
			const NumberOfStations& N_s,
			const HubRadius& r_h,
			const ShroudRadius& r_s,
			const TipClearance& z_tip
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
