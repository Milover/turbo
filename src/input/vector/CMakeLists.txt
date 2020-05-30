# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories

# add sources
set(SRC
	BladeVelocity.cpp
	InletVelocity.cpp
	InletRefPoint.cpp
	InletRelativeVelocity.cpp
	LEMonitoringPlane.cpp
	OutletVelocity.cpp
	RootOutletVelocity.cpp
	TranslationPerBot.cpp
	TranslationPerTop.cpp
	TEMonitoringPlane.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
