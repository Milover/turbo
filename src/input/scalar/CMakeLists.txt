# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories

# add sources
set(SRC
	AerodynamicEfficiency.cpp
	BezierSkewRelativeRadius.cpp
	BLFirstCellHeight.cpp
	BLGrowthRate.cpp
	BLNumberOfLayers.cpp
	BLThickness.cpp
	BLTransitionRatio.cpp
	CamberAngle.cpp
	CamberPointSpacing.cpp
	Chord.cpp
	Density.cpp
	DeviationAngle.cpp
	DynamicViscosity.cpp
	HubRadius.cpp
	HubSkewAngle.cpp
	IncidenceAngle.cpp
	InclinationAngle.cpp
	KinematicViscosity.cpp
	KinematicPressureDifference.cpp
	MaxAbsBladeThickness.cpp
	MaxCamber.cpp
	MaxCamberPosition.cpp
	MaxPassageWidth.cpp
	MaxProfileThickness.cpp
	MeshCellSize.cpp
	MonitoringPlaneOffset.cpp
	NumberOfBlades.cpp
	NumberOfCamberPoints.cpp
	NumberOfStations.cpp
	Pitch.cpp
	ProfileBumpFactor.cpp
	Radius.cpp
	RelMeshSize.cpp
	RelRadius.cpp
	Rps.cpp
	SectionExtensionFactor.cpp
	ShroudRadius.cpp
	ShroudSkewAngle.cpp
	SmootherIter.cpp
	Solidity.cpp
	StaggerAngle.cpp
	TipClearance.cpp
	StaticPressureDifference.cpp
	TurbulenceKineticEnergy.cpp
	TurbulenceIntensity.cpp
	TurbulenceDissipationRate.cpp
	TurbulenceReferenceLengthScale.cpp
	TurbulenceReferenceLengthScaleRatio.cpp
	TurbulenceSpecificDissipationRate.cpp
	TurbulenceViscosity.cpp
	VolumeFlowRate.cpp
	VortexDistributionExponent.cpp
	YPlus.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
