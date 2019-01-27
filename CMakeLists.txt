cmake_minimum_required(VERSION 3.13.0)
project(soft)
add_subdirectory(src)

option(BUILD_TESTS "Build tests" OFF)

if (BUILD_TESTS)
	add_subdirectory(tests)
	# for when tests are split into multiple binaries
	# enable_testing()
	# add_test(soft-test tests/soft-test)
	# add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
	#                   ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
	#                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

