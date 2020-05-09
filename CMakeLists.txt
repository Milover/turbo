# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

cmake_minimum_required(VERSION 3.2)

# project name
project(turbo)

# build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING
		"Choose type of build, options are: Debug Release"
		FORCE)
endif()

# install prefix
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
endif()

# compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# compiler flags
add_compile_options(
		"-Wall" "-Wextra" "-Wshadow" "-pedantic"
		"$<$<CONFIG:DEBUG>:-O0>"
		"$<$<CONFIG:RELEASE>:-march=native>"
)


# output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# search paths
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/src")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/include")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/tools/cmake")

# prerequisites
find_package(Gmsh REQUIRED)
find_package(Threads REQUIRED)

set(TURBO_INCLUDE_DIRS ${GMSH_INCLUDE_DIRS})
set(TURBO_LIBRARIES ${GMSH_LIBRARIES})
list(APPEND TURBO_LIBRARIES "Threads::Threads")
list(APPEND TURBO_LIBRARIES "stdc++fs")

# add sources macro
macro(append_turbo_src DIRNAME FILES)
	foreach(FILE ${FILES})
		list(APPEND LIST ${DIRNAME}/${FILE})
	endforeach()
	set(TURBO_SRC ${TURBO_SRC};${LIST} PARENT_SCOPE)
	set(TURBO_INCLUDE_DIRS ${TURBO_INCLUDE_DIRS};${DIRNAME} PARENT_SCOPE)
endmacro()

# enable testing
include(CTest)

# subdirectories
add_subdirectory(src)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_subdirectory(test/src)
endif()

# binary target
add_executable (turbo "${PROJECT_SOURCE_DIR}/src/Main.cpp" ${TURBO_SRC})
target_include_directories(turbo PRIVATE ${TURBO_INCLUDE_DIRS})
target_link_libraries(turbo ${TURBO_LIBRARIES})

# < new
# main library target (for tests)
add_library (libturbo SHARED ${TURBO_SRC})
set_target_properties (libturbo PROPERTIES PREFIX "")
target_include_directories(libturbo PUBLIC ${TURBO_INCLUDE_DIRS})
target_link_libraries(libturbo ${TURBO_LIBRARIES})
# < new

# install targets
install(TARGETS turbo DESTINATION "${PROJECT_SOURCE_DIR}/bin")

# documentation targets
#if(CMAKE_BUILD_TYPE MATCHES "Release")
#	add_subdirectory(doc)
#endif()
