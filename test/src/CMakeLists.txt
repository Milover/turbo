# turbo - Copyright (C) 2019 P. Milovic
#
# See the LICENSE file for license information

# compiler flags
add_compile_options(
		"-Wall" "-Wextra" "-O2"
)

# append to include directories
list(APPEND TURBO_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# add sources
file(GLOB TEST_SRC *.cpp)

# binary target
foreach(TESTFILE ${TEST_SRC})
	get_filename_component(FILENAME ${TESTFILE} NAME_WE)
	add_executable(${FILENAME} "${FILENAME}.cpp" ${TURBO_SRC})
	target_include_directories(${FILENAME} PRIVATE ${TURBO_INCLUDE_DIRS})
	target_link_libraries(${FILENAME} ${TURBO_LIBRARIES})
	set_target_properties(${FILENAME}
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/test/bin"
	)

	add_test(NAME ${FILENAME}
		COMMAND ${FILENAME} "--result-only"
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/test/bin"
	)
	set_tests_properties(${FILENAME}
		PROPERTIES
			PASS_REGULAR_EXPRESSION "1"
	)
endforeach()
