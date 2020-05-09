/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

\*---------------------------------------------------------------------------*/

#include "BLThickness.h"

#include "BLFirstCellHeight.h"
#include "BLGrowthRate.h"
#include "BLNumberOfLayers.h"
#include "BLTransitionRatio.h"
#include "ComputeGeneral.h"
#include "MeshCellSize.h"
#include "General.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace turbo
{
namespace input
{

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

BLThickness::BLThickness(const Float f)
:
	PVBase {f}
{}

BLThickness::BLThickness
(
	const BLFirstCellHeight& h_bl,
	const BLGrowthRate& k_bl,
	const BLNumberOfLayers& n_bl
)
:
	BLThickness
	{
		compute::sumNTermsGeometricSeries
		(
			h_bl.value(),
			k_bl.value(),
			n_bl.value()
		)
	}
{}


BLThickness::BLThickness
(
	const MeshCellSize& G,
	const BLFirstCellHeight& h_bl,
	const BLTransitionRatio& k,
	const BLGrowthRate& k_bl
)
:
	BLThickness
	{
		compute::computeBLThickness
		(
			G.value(),
			h_bl.value(),
			k.value(),
			k_bl.value()
		)
	}
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace input
} // End namespace turbo

// ************************************************************************* //
