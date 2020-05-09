# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add all subdirectories
add_subdirectory(detail)
add_subdirectory(operators)

# add sources
set(SRC
	Bezier.cpp
	Curve.cpp
	Line.cpp
	Model.cpp
	PlanarSurface.cpp
	Point.cpp
	Spline.cpp
	Surface.cpp
	Volume.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
