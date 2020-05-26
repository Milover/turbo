# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories

# add sources
set(SRC
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
	IncidenceAngle.cpp
	InclinationAngle.cpp
	KinematicViscosity.cpp
	MaxCamber.cpp
	MaxCamberPosition.cpp
	MaxProfileThickness.cpp
	MeshCellSize.cpp
	MeshSize.cpp
	MonitoringPlaneOffset.cpp
	NumberOfBlades.cpp
	NumberOfCamberPoints.cpp
	NumberOfStations.cpp
	Pitch.cpp
	ProfileBumpFactor.cpp
	Radius.cpp
	Rps.cpp
	SectionExtensionFactor.cpp
	ShroudRadius.cpp
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
