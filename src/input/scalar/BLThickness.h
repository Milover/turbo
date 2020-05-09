/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Class
	turbo::input::BLThickness

Description
	Class BLThickness.

SourceFiles
	BLThickness.cpp

\*---------------------------------------------------------------------------*/

#ifndef INPUT_BL_THICKNESS_H
#define INPUT_BL_THICKNESS_H

#include "BLFirstCellHeight.h"
#include "BLGrowthRate.h"
#include "BLNumberOfLayers.h"
#include "BLTransitionRatio.h"
#include "MeshCellSize.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

/*---------------------------------------------------------------------------*\
						Class BLThickness Declaration
\*---------------------------------------------------------------------------*/

class BLThickness final
:
	public PositiveValue<Float>
{
public:

	// Public static data

		inline static const String name {"BLThickness"};


	// Constructors

		//- Construct from a Float,
		//  no aditional checking required
		explicit BLThickness(const Float f);

		//- Compute and construct
		BLThickness
		(
			const BLFirstCellHeight& h_bl,
			const BLGrowthRate& k_bl,
			const BLNumberOfLayers& n_bl
		);

		//- Compute and construct
		BLThickness
		(
			const MeshCellSize& G,
			const BLFirstCellHeight& h_bl,
			const BLTransitionRatio& k,
			const BLGrowthRate& k_bl
		);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
