# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories
add_subdirectory(compute)
add_subdirectory(design)
add_subdirectory(general)
add_subdirectory(geometry)
add_subdirectory(input)
add_subdirectory(interface)
add_subdirectory(math)
add_subdirectory(mesh)
add_subdirectory(simulation)

# add sources
set(SRC
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
