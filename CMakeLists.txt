# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

cmake_minimum_required(VERSION 3.2)

# project name
project(turbo)

# build type
if(DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose build type")
else()
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type")
endif()

# install prefix
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
endif()

# compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

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
include_directories(${GMSH_INCLUDE_DIRS})

list(APPEND TURBO_INCLUDE_DIRS ${GMSH_INCLUDE_DIRS})
list(APPEND TURBO_LIBRARIES ${GMSH_LIBRARIES})

# build targets
add_subdirectory(src)
#add_subdirectory(test)

# documentation targets
if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
	add_subdirectory(doc)
endif()
