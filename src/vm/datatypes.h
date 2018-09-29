#ifndef _SOFT_VM_DATATYPES_H
#define _SOFT_VM_DATATYPES_H

#include <stdio.h>
#include <stdint.h>

enum soft_datatypes {
	soft_ptr,
	soft_int32,
	soft_float,
};

union SoftData {
	int32_t   soft_int32;
	float     soft_float;
	void *    soft_ptr;
};

typedef int32_t soft_int32_t;
typedef float soft_float_t;
typedef void * soft_ptr_t;

#endif // _SOFT_VM_DATATYPES_H
