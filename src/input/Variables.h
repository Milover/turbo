/*---------------------------------------------------------------------------*\

	turbo - Copyright (C) 2019 P. Milovic

-------------------------------------------------------------------------------
License
	See the LICENSE file for license information.

Description
	Header for easier loading of variables.

\*---------------------------------------------------------------------------*/

#ifndef INPUT_VARIABLES_H
#define INPUT_VARIABLES_H

#include "RegistryObject.h"
#include "RegistryObjectBase.h"

// scalars
#include "BezierSkewRelativeRadius.h"
#include "BLFirstCellHeight.h"
#include "BLGrowthRate.h"
#include "BLNumberOfLayers.h"
#include "BLThickness.h"
#include "BLTransitionRatio.h"
#include "CamberAngle.h"
#include "CamberPointSpacing.h"
#include "Chord.h"
#include "Density.h"
#include "DeviationAngle.h"
#include "DynamicViscosity.h"
#include "HubRadius.h"
#include "HubSkewAngle.h"
#include "IncidenceAngle.h"
#include "InclinationAngle.h"
#include "KinematicViscosity.h"
#include "MaxProfileThickness.h"
#include "MaxCamber.h"
#include "MaxCamberPosition.h"
#include "MeshCellSize.h"
#include "MonitoringPlaneOffset.h"
#include "NumberOfBlades.h"
#include "NumberOfCamberPoints.h"
#include "NumberOfStations.h"
#include "Pitch.h"
#include "ProfileBumpFactor.h"
#include "Radius.h"
#include "RelMeshSize.h"
#include "Rps.h"
#include "SectionExtensionFactor.h"
#include "ShroudRadius.h"
#include "ShroudSkewAngle.h"
#include "SmootherIter.h"
#include "Solidity.h"
#include "StaggerAngle.h"
#include "TipClearance.h"
#include "StaticPressureDifference.h"
#include "TurbulenceKineticEnergy.h"
#include "TurbulenceIntensity.h"
#include "TurbulenceDissipationRate.h"
#include "TurbulenceReferenceLengthScale.h"
#include "TurbulenceReferenceLengthScaleRatio.h"
#include "TurbulenceSpecificDissipationRate.h"
#include "TurbulenceViscosity.h"
#include "VolumeFlowRate.h"
#include "VortexDistributionExponent.h"
#include "YPlus.h"

// vectors
#include "BladeVelocity.h"
#include "InletVelocity.h"
#include "InletRefPoint.h"
#include "InletRelativeVelocity.h"
#include "LEMonitoringPlane.h"
#include "OutletVelocity.h"
#include "RootOutletVelocity.h"
#include "TranslationPerBot.h"
#include "TranslationPerTop.h"
#include "TEMonitoringPlane.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
