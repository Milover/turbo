# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add sources
set(SRC
	CamberGeneratorBase.cpp
	CircularArcCamber.cpp
	Naca2DigitCamber.cpp
	NoCamber.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
