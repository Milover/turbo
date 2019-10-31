# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# append current directory to link list
list(APPEND TURBO_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# add object library sources
set(SRC
	Shape.cpp
	Point.cpp
	Line.cpp
	Vector.cpp
	)

# add object library
add_library(geometry OBJECT ${SRC})
list(APPEND OBJECTS $<TARGET_OBJECTS:geometry>)
target_include_directories(geometry
	PUBLIC
		${TURBO_INCLUDE_DIRS}
	)
target_link_libraries(geometry
	PUBLIC
		${TURBO_LIBRARIES}
	)

set(OBJECTS ${OBJECTS} PARENT_SCOPE)

# append to link list
list(APPEND TURBO_LIBRARIES "geometry")
