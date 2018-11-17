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
bool sval_is_nan(sval_t v);
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
sval_t sval_nan();

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

int32_t sval_cast_to_int(sval_t val);
double  sval_cast_to_double(sval_t val);
char *  sval_cast_to_string(sval_t val);

#define sval_arithmetic(var, left, op, right) \
	do { \
\
		if (sval_is_int(left)) { \
\
			if (sval_is_double(right) \
				|| (sval_is_string(right) && str_is_double(sval_to_string(right)))) { \
				var = sval_from_double(sval_cast_to_double(left) op sval_cast_to_double(right)); \
			} \
			else if (sval_is_int(right) \
				|| (sval_is_string(right) && str_is_int(sval_to_string(right)))) \
				var = sval_from_int(sval_to_int(left) op sval_cast_to_int(right)); \
			else \
				var = sval_nan(); \
\
		} \
		else if (sval_is_double(left)) { \
\
			if (sval_is_number(right) \
				|| (sval_is_string(right) && str_is_number(sval_to_string(right)))) \
				var = sval_from_double(sval_cast_to_double(left) op sval_cast_to_double(right)); \
			else \
				var = sval_nan(); \
\
		} \
		else if (sval_is_string(left)) { \
\
			char * strleft = sval_to_string(left); \
\
			if (sval_is_string(right)) { \
\
				char * strright = sval_to_string(right); \
\
				if (str_is_number(strleft) && str_is_number(strright)) { \
					if (str_is_double(strleft) || str_is_double(strright)) \
						var = sval_from_double(sval_cast_to_double(left) op sval_cast_to_double(right)); \
					else \
						var = sval_from_int(sval_cast_to_int(left) op sval_cast_to_int(right)); \
				} \
				else { \
					var = sval_nan(); \
				} \
\
			} \
			else if (str_is_number(strleft) && sval_is_number(right)) { \
\
				if (sval_is_double(right) || str_is_double(strleft)) \
					var = sval_from_double(sval_cast_to_double(left) op sval_cast_to_double(right)); \
				else \
					var = sval_from_int(sval_cast_to_int(left) op sval_cast_to_int(right)); \
\
			} \
			else { \
				var = sval_nan(); \
			} \
\
		} \
		else { \
			var = sval_nan(); \
		} \
\
	} while (0)

#endif // _SOFT_NANBOX_H
