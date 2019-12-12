# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# add sources
set(SRC
	Curve.cpp
	Line.cpp
	Point.cpp
	Shape.cpp
	Spline.cpp
	Surface.cpp
	SurfaceFilling.cpp
	SurfaceSection.cpp
	)

# append to sources
file(GLOB HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
append_turbo_src(${CMAKE_CURRENT_SOURCE_DIR} "${SRC};${HDR}")
