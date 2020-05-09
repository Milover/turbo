/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BLFirstCellHeight

Description
	Class BLFirstCellHeight.

SourceFiles
	BLFirstCellHeight.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BL_FIRST_CELL_HEIGHT_H
#define INPUT_BL_FIRST_CELL_HEIGHT_H

#include "BladeVelocity.h"
#include "Chord.h"
#include "Density.h"
#include "DynamicViscosity.h"
#include "General.h"
#include "InletVelocity.h"
#include "YPlus.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
					Class BLFirstCellHeight Declaration
\*---------------------------------------------------------------------------*/

class BLFirstCellHeight final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"BLFirstCellHeight"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit BLFirstCellHeight(const Float f);

		//- Compute and construct
		BLFirstCellHeight
		(
			const InletVelocity& c_1,
			const BladeVelocity& U,
			const Chord& c,
			const DynamicViscosity& mu,
			const Density& rho,
			const YPlus& y_plus
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
