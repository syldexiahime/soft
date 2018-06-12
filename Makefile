SRC_FILES = soft-vm.c
CC_FLAGS = -std=c11
CC = clang

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o soft
