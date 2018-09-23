#ifndef _SOFT_VM_DATATYPES_H
#define _SOFT_VM_DATATYPES_H

#include <stdio.h>
#include <stdint.h>

typedef enum {
	soft_ptr = 0x00,
	soft_int32 = 0x10,
	soft_float = 0x20,
} soft_DATATYPES;

union SoftData {
	int32_t   soft_int32;
	float     soft_float;
	void *    soft_ptr;
};

typedef int32_t soft_int32_t;
typedef float soft_float_t;
typedef void * soft_ptr_t;

#endif // _SOFT_VM_DATATYPES_H
