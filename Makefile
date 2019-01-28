.PHONY: all dev test clean

BUILD_DIR = build
BUILD_FLAGS =
DEV_FLAGS = BUILD_TESTS=1

ifneq (${BUILD_FLAGS},)
	_BUILD_FLAGS = -D ${BUILD_FLAGS}
endif

ifneq (${BUILD_FLAGS}${DEV_FLAGS},)
	_DEV_FLAGS = -D ${BUILD_FLAGS} ${DEV_FLAGS}
endif

all:
	(mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ${_BUILD_FLAGS} .. && make)

dev:
	(mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && cmake ${_DEV_FLAGS} .. && make)

test:
	make -C ${BUILD_DIR} test

coverage:
	make -C ${BUILD_DIR} coverage

clean:
	rm -r ${BUILD_DIR}

