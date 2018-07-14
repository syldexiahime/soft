SRC_FILES = src/soft.c src/**/*.c
CC_FLAGS = -std=c11
CC = clang
HEADER_DIRS = -I'src'

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} ${HEADER_DIRS} -o soft
