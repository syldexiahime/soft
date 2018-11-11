#ifndef _SOFT_SVAL_H
#define _SOFT_SVAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "utils/tagged-pointer.h"

union sval {
	uint64_t as_bits;
	int64_t  as_int;
	double   as_double;
	void *   as_ptr;
	char     as_chars[8];
};

typedef union sval sval_t;

sval_t sval_from_bits(uint64_t bits);

bool sval_is_null(sval_t v);
bool sval_is_true(sval_t v);
bool sval_is_false(sval_t v);
bool sval_is_bool(sval_t v);
bool sval_is_number(sval_t v);
bool sval_is_int(sval_t v);
bool sval_is_double(sval_t v);
bool sval_is_pointer(sval_t v);
bool sval_is_tagged_pointer(sval_t v);
bool sval_is_string(sval_t v);
bool sval_is_truthy(sval_t v);
bool sval_is_falsey(sval_t v);

sval_t sval_null();
sval_t sval_true();
sval_t sval_false();

sval_t sval_from_bool(bool);
bool sval_to_bool(sval_t v);

sval_t sval_from_int(int32_t);
int32_t sval_to_int(sval_t v);

sval_t sval_from_double(double d);
double sval_to_double(sval_t v);

sval_t sval_from_pointer(void * ptr);
void * sval_to_pointer(sval_t v);

sval_t sval_from_string(char * ptr);
char * sval_to_string(sval_t v);

#endif // _SOFT_NANBOX_H
