.PHONY: all test clean

CC = clang
CC_FLAGS = -std=c99
HEADER_DIRS = -I'src'

MAIN = src/soft.c
SRC_FILES = src/**/*.c

TEST_MAIN = tests/soft-test.c
TEST_FILES = tests/**/*.c
TEST_LIBS = -lcmocka
TEST_HEADER_DIRS = -I'tests'
# TEST_FLAGS = -fprofile-arcs -ftest-coverage
COVERAGE_FLAGS = -fprofile-instr-generate -fcoverage-mapping

LINT_FLAGS = -fsyntax-only -Wall -Wextra

all:
	${CC} ${MAIN} ${SRC_FILES} ${CC_FLAGS} ${HEADER_DIRS} -o build/soft

test:
	${CC} ${TEST_MAIN} ${SRC_FILES} ${TEST_FILES} ${CC_FLAGS} \
	${HEADER_DIRS} ${TEST_HEADER_DIRS} ${TEST_FLAGS} ${TEST_LIBS} \
	 -o build/soft-tests
	./build/soft-tests

coverage:
	${CC} ${TEST_MAIN} ${SRC_FILES} ${TEST_FILES} ${CC_FLAGS} \
	${HEADER_DIRS} ${TEST_HEADER_DIRS} ${TEST_FLAGS} ${TEST_LIBS} \
	${COVERAGE_FLAGS} -o build/soft-coverage
	LLVM_PROFILE_FILE="build/soft.profraw" ./build/soft-coverage
	llvm-profdata merge -sparse build/soft.profraw -o build/soft.profdata
	llvm-cov report ./build/soft-coverage -instr-profile=build/soft.profdata

lint:
	${CC} ${MAIN} ${SRC_FILES} ${CC_FLAGS} ${LINT_FLAGS} ${HEADER_DIRS}
