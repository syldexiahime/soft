#include "vm/sval.h"

#define NANBOX_DOUBLE_ENCODE_OFFSET 0x0007000000000000ul
#define NANBOX_MIN_NUMBER           0x0006000000000000ul
#define NANBOX_HIGH16_TAG           0xffff000000000000ul
#define NANBOX_POINTER_MASK         0x0000fffffffffffcul

#define NANBOX_VALUE_NULL  0b000ul
#define NANBOX_VALUE_TRUE  0b110ul
#define NANBOX_VALUE_FALSE 0b111ul

#define SVAL_STRING_POINTER_TAG 0b11

inline union sval sval_from_bits(uint64_t bits)
{
	union sval v;
	v.as_bits = bits;

	return v;
}

inline bool sval_is_null(union sval val)  { return val.as_int == NANBOX_VALUE_NULL;  }
inline bool sval_is_true(union sval val)  { return val.as_int == NANBOX_VALUE_TRUE;  }
inline bool sval_is_false(union sval val) { return val.as_int == NANBOX_VALUE_FALSE; }

inline union sval sval_null()  { union sval val; val.as_int = NANBOX_VALUE_NULL;  return val; }
inline union sval sval_true()  { union sval val; val.as_int = NANBOX_VALUE_TRUE;  return val; }
inline union sval sval_false() { union sval val; val.as_int = NANBOX_VALUE_FALSE; return val; }

inline bool sval_is_bool(union sval val)
{
	return (val.as_int & ~1) == NANBOX_VALUE_TRUE;
}

inline union sval sval_from_bool(bool b)
{
	union sval val;
	val.as_int = b ? NANBOX_VALUE_TRUE : NANBOX_VALUE_FALSE;
	return val;
}

bool sval_to_bool(union sval val)
{
	return !(val.as_int & 1);
}

inline bool sval_is_number(union sval val)
{
	return val.as_int >= NANBOX_MIN_NUMBER;
}

inline bool sval_is_int(union sval val)
{
	return (val.as_int & NANBOX_HIGH16_TAG) == NANBOX_MIN_NUMBER;
}

inline union sval sval_from_int(int32_t i)
{
	union sval v;
	v.as_bits = NANBOX_MIN_NUMBER | (uint32_t) i;

	return v;
}

inline int32_t sval_to_int(union sval val)
{
	assert(sval_is_int(val));
	return (int32_t) val.as_int;
}

inline bool sval_is_double(union sval val)
{
	return sval_is_number(val) && !sval_is_int(val);
}

inline union sval sval_from_double(double d)
{
	union sval val;
	val.as_double = d;
	val.as_int += NANBOX_DOUBLE_ENCODE_OFFSET;

	return val;
}

inline double sval_to_double(union sval val)
{
	assert(sval_is_double(val));
	val.as_int -= NANBOX_DOUBLE_ENCODE_OFFSET;

	return val.as_double;
}

inline bool sval_is_pointer(union sval val)
{
	uint64_t untagged = val.as_int & ~TAGGED_POINTER_MASK;

	return untagged && !(untagged & ~NANBOX_POINTER_MASK);
}

inline union sval sval_from_pointer(void * ptr)
{
	union sval v;
	v.as_bits = (int64_t) ptr;

	return v;
}

inline void * sval_to_pointer(union sval v)
{
	assert(sval_is_pointer(v));
	v.as_int = (v.as_int << 16) >> 16;

	return v.as_ptr;
}

inline bool sval_is_tagged_pointer(union sval val)
{
	return sval_is_pointer(val) && is_tagged_pointer(sval_to_pointer(val));
}

inline bool sval_is_string(union sval val)
{
	return sval_is_tagged_pointer(val) && check_pointer_tag(sval_to_pointer(val), SVAL_STRING_POINTER_TAG);
}

inline union sval sval_from_string(char * ptr)
{
	char * tptr = tag_pointer(ptr, SVAL_STRING_POINTER_TAG);

	return sval_from_pointer(tptr);
}

inline char * sval_to_string(union sval val)
{
	assert(sval_is_string(val));
	return untag_pointer(sval_to_pointer(val));
}

inline bool sval_is_truthy(union sval v)
{
	return (sval_is_true(v))
		|| (sval_is_int(v)     && sval_to_int(v)     != 0)
		|| (sval_is_pointer(v) && sval_to_pointer(v) != NULL)
		|| (sval_is_string(v)  && strcmp(sval_to_string(v), "") != 0)
		|| (sval_is_double(v)  && sval_to_double(v)  != 0.0);
}

inline bool sval_is_falsey(union sval v)
{
	return (sval_is_false(v))
		|| (sval_is_null(v))
		|| (sval_is_int(v)     && sval_to_int(v)     == 0)
		|| (sval_is_pointer(v) && sval_to_pointer(v) == NULL)
		|| (sval_is_string(v)  && strcmp(sval_to_string(v), "") == 0)
		|| (sval_is_double(v)  && sval_to_double(v)  == 0.0);
}

inline int32_t sval_cast_to_int(union sval val)
{
	if (sval_is_int(val))    return           sval_to_int(val);

	if (sval_is_double(val)) return (int32_t) sval_to_double(val);

	if (sval_is_string(val)) {

		char * str = sval_to_string(val);

		if (isnumber(str[0])) {

			if (strstr(str, "."))
				return (int32_t) parse_double(str);
			else
				return parse_int(str);

		}

	}

	return 0;
}

inline double sval_cast_to_double(union sval val)
{
	if (sval_is_int(val))    return (double) sval_to_int(val);

	if (sval_is_double(val)) return         sval_to_double(val);

	if (sval_is_string(val)) {

		char * str = sval_to_string(val);

		if (isnumber(str[0])) {

			if (strstr(str, "."))
				return parse_double(str);
			else
				return (double) parse_int(str);

		}

	}

	return (double) 0;
}

inline char * sval_cast_to_string(union sval val)
{
	if (sval_is_int(val))    return int_to_str(sval_to_int(val));

	if (sval_is_double(val)) return double_to_str(sval_to_double(val));

	if (sval_is_string(val)) return sval_to_string(val);

	return NULL;
}
