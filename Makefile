.PHONY: all test clean

CC = clang
CC_FLAGS = -std=c11
HEADER_DIRS = -I'src'

MAIN = src/soft.c
SRC_FILES = src/**/*.c

TEST_MAIN = tests/soft-test.c
TEST_FILES = tests/**/*.c
TEST_LIBS = -lcmocka
TEST_HEADER_DIRS = -I'tests'
# TEST_FLAGS = -fprofile-arcs -ftest-coverage

LINT_FLAGS = -fsyntax-only -Wall -Wextra

all:
	${CC} ${MAIN} ${SRC_FILES} ${CC_FLAGS} ${HEADER_DIRS} -o soft

test:
	${CC} ${TEST_MAIN} ${SRC_FILES} ${TEST_FILES} ${CC_FLAGS} \
	${HEADER_DIRS} ${TEST_HEADER_DIRS} ${TEST_FLAGS} ${TEST_LIBS} \
	 -o soft-tests
	./soft-tests

lint:
	${CC} ${MAIN} ${SRC_FILES} ${CC_FLAGS} ${LINT_FLAGS} ${HEADER_DIRS}
