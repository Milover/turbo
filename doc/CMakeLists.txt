# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# check if Doxygen is present
find_package(Doxygen)

# build
if(DOXYGEN_FOUND)
	set(DOXYFILE "${PROJECT_SOURCE_DIR}/doc/Doxyfile")

	add_custom_target(
		doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/doc"
		COMMENT "Generating documentation with Doxygen"
		VERBATIM
		)
else()
	message(FATAL_ERROR "Doxygen is required to build the documentation.")
endif()
