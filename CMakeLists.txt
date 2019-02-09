cmake_minimum_required(VERSION 3.13.0)
project(soft)
add_subdirectory(src)

option(BUILD_TESTS "Build tests" OFF)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
	add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
	                  ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
	                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	add_custom_target(test-verbose COMMAND ${CMAKE_CTEST_COMMAND} --verbose WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

