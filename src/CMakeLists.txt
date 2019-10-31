# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# compiler flags
add_compile_options(
		"-Wall" "-Wextra"
		"$<$<CONFIG:DEBUG>:-O0>"
		"$<$<CONFIG:RELEASE>:-O3>"
)

list(APPEND TURBO_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# add sources
set(SRC
	Main.cpp
	turbo.cpp
	)
# add subdirectories for inclusion
set(DIRS
	geometry
	)

# need for the object libraries
set(OBJECTS)

# add all subdirectories
add_subdirectory(geometry)

# main static library for the executable
add_library(libturbo STATIC ${OBJECTS})
set_target_properties(libturbo PROPERTIES PREFIX "")

# append include and link lists
list(APPEND TURBO_INCLUDE_DIRS ${DIRS})
list(APPEND TURBO_LIBRARIES "libturbo")

# binary target
add_executable(turbo ${SRC})
target_include_directories(turbo PUBLIC ${TURBO_INCLUDE_DIRS})
target_link_libraries(turbo ${TURBO_LIBRARIES})

# install targets
install(TARGETS turbo DESTINATION "${PROJECTS_SOURCE_DIR}/bin")
