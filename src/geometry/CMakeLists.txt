# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories
add_subdirectory(basic)
add_subdirectory(manipulation)
add_subdirectory(primitive)
add_subdirectory(profile)

# add sources
set(SRC
	Airfoil.cpp
	Blade.cpp
	BladeRow.cpp
	CarterDeviation.cpp
	ComponentBase.cpp
	DeHallerCriterion.cpp
	Deviation.cpp
	Machine.cpp
	McKenzieDeviation.cpp
	Profile.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
