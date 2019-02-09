file(GLOB_RECURSE SOURCES "../src/**/*.c")
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE TEST_SOURCES "**/*.c")
file(GLOB_RECURSE TEST_HEADERS "*.h")


################################################
# Set test coverate stuff
################################################

option(TEST_COVERAGE "Test coverage" OFF)
if (TEST_COVERAGE)
	if (CMAKE_C_COMPILER_ID MATCHES "Clang")
		SET(GENERATE_COVERAGE 1)
		SET(COVERAGE_COMPILE_FLAGS -fprofile-instr-generate -fcoverage-mapping)
		SET(COVERAGE_LINK_FLAGS -fprofile-instr-generate -fcoverage-mapping)
		SET(PROFDATA_COMMAND " ")
		SET(COVERAGE_COMMAND " ")

		if (APPLE)
			SET(XCRUN xcrun)
		endif()
	else ()
		message(WARNING "TEST COVERAGE ONLY SUPPORTED WITH CLANG")
	endif ()
else ()
	#add_custom_target(test sh -c "./soft-test")
	add_custom_target(coverage sh -c "echo COVERAGE NOT ENABLED")
endif ()


################################################
# Make list of tests
################################################

list(APPEND tests_names "utils-tests")
list(APPEND tests_flags " ")
list(APPEND tests_c_files "utils-tests")

list(APPEND tests_names "sval-tests")
list(APPEND tests_flags " ")
list(APPEND tests_c_files "sval-tests")

list(APPEND tests_names "instr-tests")
list(APPEND tests_flags " ")
list(APPEND tests_c_files "instr-tests")

if (CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
	list(APPEND tests_names "instr-tests-no-computed-goto")
	list(APPEND tests_flags "-DSOFT_VM_USE_COMPUTED_GOTO=0")
	list(APPEND tests_c_files "instr-tests")
endif ()


################################################
# Declare all tests targets
################################################

list(LENGTH tests_names count)
math(EXPR count "${count} - 1")
foreach(i RANGE ${count})
	list(GET tests_names ${i} test_name)
	list(GET tests_flags ${i} test_flags)
	list(GET tests_c_files ${i} test_c_file)

	add_executable(${test_name} ${test_c_file}.c ${SOURCES} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS})
	target_link_libraries(${test_name} cmocka)
	target_include_directories(${test_name} PRIVATE ../include ../tests)
	target_compile_options(${test_name} PRIVATE ${COVERAGE_COMPILE_FLAGS})
	target_link_options(${test_name} PRIVATE ${COVERAGE_LINK_FLAGS})

	if (NOT test_flags STREQUAL " ")
		target_compile_definitions(${test_name} PRIVATE ${test_flags})
	endif ()

	add_test(${test_name} ${test_name})
	set_property(TEST ${test_name} PROPERTY ENVIRONMENT LLVM_PROFILE_FILE=${test_name}.profraw)

	if (GENERATE_COVERAGE)
		SET(PROFDATA_COMMAND "${PROFDATA_COMMAND} ${XCRUN} llvm-profdata merge -sparse ${test_name}.profraw -o ${test_name}.profdata;")
		SET(COVERAGE_COMMAND "${COVERAGE_COMMAND} ${XCRUN} llvm-cov show ${test_name} -instr-profile=${test_name}.profdata | sed '/^\\/.*\\/tests\\/.*:$/,/^$/d' > coverage/${test_name}.coverage.txt;")
	endif ()
endforeach()

if (GENERATE_COVERAGE)
	add_custom_target(profdata sh -c "${PROFDATA_COMMAND}" VERBATIM)
	add_custom_target(coverage DEPENDS profdata COMMAND sh -c "mkdir -p coverage && ${COVERAGE_COMMAND} " VERBATIM)
endif ()

