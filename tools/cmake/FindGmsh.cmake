# - Try to find Gmsh
# Once done this will define
#  GMSH_FOUND - System has Gmsh
#  GMSH_INCLUDE_DIRS - The Gmsh include directories
#  GMSH_LIBRARIES - The libraries needed to use Gmsh
#  GMSH_DEFINITIONS - Compiler switches required for using Gmsh

find_package(PkgConfig)
pkg_check_modules(PC_GMSH QUIET gmsh)
set(GMSH_DEFINITIONS ${PC_GMSH_CFLAGS_OTHER})

find_path(GMSH_INCLUDE_DIR gmsh.h
	HINTS ${GMSH_INCLUDEDIR} ${GMSH_INCLUDE_DIRS}
	PATH_SUFFIXES gmsh
	)

find_library(GMSH_LIBRARY NAMES gmsh
	HINTS ${PC_GMSH_LIBDIR} ${PC_GMSH_LIBRARY_DIRS}
	)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GMSH_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GMSH  DEFAULT_MSG
	GMSH_LIBRARY GMSH_INCLUDE_DIR
	)

mark_as_advanced(GMSH_INCLUDE_DIR GMSH_LIBRARY)

set(GMSH_LIBRARIES ${GMSH_LIBRARY})
set(GMSH_INCLUDE_DIRS ${GMSH_INCLUDE_DIR})

