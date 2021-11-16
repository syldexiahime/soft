.PHONY: all dev test check test-verbose clean

BUILD_DIR = build
BUILD_FLAGS =
DEV_FLAGS = -D BUILD_TESTS=1
COVERAGE_FLAGS = -D TEST_COVERAGE=1

MAKE_FLAGS = --directory=${BUILD_DIR} --no-print-directory -s

ifneq (${BUILD_FLAGS},)
	_BUILD_FLAGS = ${BUILD_FLAGS}
endif

ifneq (${_BUILD_FLAGS}${DEV_FLAGS},)
	_DEV_FLAGS = ${_BUILD_FLAGS} ${DEV_FLAGS}
endif

ifneq (${_DEV_FLAGS}${COVERAGE_FLAGS},)
	_COVERAGE_FLAGS = ${_DEV_FLAGS} ${COVERAGE_FLAGS}
endif

all:
	@(mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake -D NDEBUG=1 ${_BUILD_FLAGS} .. && make --no-print-directory)

dev:
	@(mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ${_DEV_FLAGS} .. && make --no-print-directory)

test:
	@make ${MAKE_FLAGS} test

check:
	@make ${MAKE_FLAGS} check

test-verbose:
	@make ${MAKE_FLAGS} test-verbose

coverage:
	@grep -q TEST_COVERAGE:BOOL=1 "${BUILD_DIR}/CMakeCache.txt" || (mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ${_COVERAGE_FLAGS} .. && make)
	@test "$$(find ${BUILD_DIR}/tests/ -name '*.profraw' -print -quit)" || make ${MAKE_FLAGS} test
	@make ${MAKE_FLAGS} coverage

clean:
	rm -r "${BUILD_DIR}"
	@mkdir -p "${BUILD_DIR}"

