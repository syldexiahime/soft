file(GLOB_RECURSE SOURCES "../src/**/*.c")
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE TEST_SOURCES "**/*.c")
file(GLOB_RECURSE TEST_HEADERS "*.h")

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
	SET(COVERAGE_COMPILE_FLAGS -fprofile-instr-generate -fcoverage-mapping)
	SET(COVERAGE_LINK_FLAGS -fprofile-instr-generate -fcoverage-mapping)

	if (APPLE)
		SET(XCRUN xcrun)
	endif()

	add_custom_target(test sh -c "LLVM_PROFILE_FILE='soft.profraw' ./soft-test")
	add_custom_target(profdata sh -c "${XCRUN} llvm-profdata merge -sparse soft.profraw -o soft.profdata")
	add_custom_target(coverage DEPENDS profdata COMMAND sh -c "${XCRUN} llvm-cov show ./soft-test -instr-profile=soft.profdata | sed '/^\\/.*\\/tests\\/.*:$/,/^$/d'" VERBATIM)
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET(COVERAGE_COMPILE_FLAGS -fprofile-arcs -ftest-coverage)
	SET(COVERAGE_LINK_FLAGS    -lgcov)

	add_custom_target(test sh -c "./soft-test")
	add_custom_target(coverage sh -c "gcov ./soft-test")
endif()

add_executable(soft-test soft-test.c ${SOURCES} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS})
target_include_directories(soft-test PRIVATE ../include ../tests)
target_link_libraries(soft-test cmocka)
target_compile_options(soft-test PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_options(soft-test PRIVATE ${COVERAGE_LINK_FLAGS})


