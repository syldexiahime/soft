SRC_FILES = soft-vm.c
CC_FLAGS = -std=c11
CC = gcc

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o soft
