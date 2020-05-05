# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories

# add sources
set(SRC
	CamberAngle.cpp
	CamberPointSpacing.cpp
	Chord.cpp
	Density.cpp
	HubRadius.cpp
	IncidenceAngle.cpp
	InclinationAngle.cpp
	MaxCamber.cpp
	MaxCamberPosition.cpp
	MaxProfileThickness.cpp
	NumberOfBlades.cpp
	NumberOfCamberPoints.cpp
	Pitch.cpp
	Radius.cpp
	Rps.cpp
	ShroudRadius.cpp
	SmootherIter.cpp
	Solidity.cpp
	StaggerAngle.cpp
	TotalPressureDifference.cpp
	VolumeFlowRate.cpp
	VortexDistributionExponent.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
