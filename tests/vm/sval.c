#include "vm/vm-test.h"
#include <math.h>

static union sval v;

void soft_test_sval_null(void ** state)
{
	v = sval_null();

	assert_true(sval_is_null(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_false(sval_is_truthy(v));
	assert_true(sval_is_falsey(v));
}

void soft_test_sval_nan(void ** state)
{
	v = sval_nan();

	assert_true(sval_is_nan(v));

	assert_false(sval_is_null(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_false(sval_is_truthy(v));
	assert_true(sval_is_falsey(v));
}

void soft_test_sval_true(void ** state)
{
	v = sval_true();

	assert_true(sval_is_bool(v));
	assert_true(sval_is_true(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_false(v));

	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));
}

void soft_test_sval_false(void ** state)
{
	v = sval_false();

	assert_true(sval_is_bool(v));
	assert_true(sval_is_false(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));

	assert_false(sval_is_truthy(v));
	assert_true(sval_is_falsey(v));
}

void soft_test_sval_bool(void ** state)
{
	bool b;

	b = true;
	v = sval_from_bool(b);

	assert_true(sval_is_bool(v));
	assert_true(sval_is_true(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_false(v));

	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));

	assert_true(sval_to_bool(v) == b);

	b = false;
	v = sval_from_bool(b);

	assert_true(sval_is_bool(v));
	assert_true(sval_is_false(v));

	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));

	assert_false(sval_is_truthy(v));
	assert_true(sval_is_falsey(v));

	assert_true(sval_to_bool(v) == b);
}

void soft_test_sval_pointer(void ** state)
{
	v = sval_from_pointer(&v);

	assert_true(sval_is_pointer(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));

	assert_true(v.as_ptr == &v);
	assert_true(sval_to_pointer(v) == &v);
}

void soft_test_sval_double(void ** state)
{
	double d = 123.45;
	v = sval_from_double(d);

	assert_true(sval_is_number(v));
	assert_true(sval_is_double(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));

	assert_true(v.as_double != d);
	assert_true(sval_to_double(v) == d);
}

void soft_test_sval_int(void ** state)
{
	int i = 12345;
	v = sval_from_int(i);

	assert_true(sval_is_number(v));
	assert_true(sval_is_int(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_pointer(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));

	assert_true(v.as_int != (int64_t) i);
	assert_true(sval_to_int(v) == i);
}

void soft_test_sval_string(void ** state)
{
	char * str = malloc(sizeof(char) * 5);
	strcpy(str, "Hello");

	v = sval_from_string(str);

	assert_true(sval_is_string(v));
	assert_true(sval_is_pointer(v));

	assert_false(sval_is_nan(v));
	assert_false(sval_is_number(v));
	assert_false(sval_is_double(v));
	assert_false(sval_is_int(v));
	assert_false(sval_is_null(v));
	assert_false(sval_is_true(v));
	assert_false(sval_is_false(v));

	assert_false(sval_is_bool(v));
	assert_true(sval_is_truthy(v));
	assert_false(sval_is_falsey(v));

	assert_true(v.as_ptr != str);
	assert_true(strcmp(sval_to_string(v), str) == 0);
}

void soft_test_sval_falsey(void ** state)
{
	v = sval_from_int(0);
	assert_true(sval_is_falsey(v));
	v = sval_from_double(0.0f);
	assert_true(sval_is_falsey(v));
	v = sval_from_pointer(NULL);
	assert_true(sval_is_falsey(v));
	v = sval_null();
	assert_true(sval_is_falsey(v));
}

void soft_test_sval_casts(void ** state)
{
	v = sval_from_int(35);
	assert_true(sval_cast_to_double(v) == (double) 35);
	assert_true(strcmp(sval_cast_to_string(v), "35") == 0);

	v = sval_from_double(23.45);
	assert_true(sval_cast_to_int(v) == 23);
	assert_true(strcmp(sval_cast_to_string(v), "23.450000") == 0);


	char * str = malloc(sizeof(char) * 5);

	strcpy(str, "35");

	v = sval_from_string(str);
	assert_true(sval_cast_to_int(v) == 35);
	assert_true(sval_cast_to_double(v) == (double) 35);

	strcpy(str, "23.45");

	v = sval_from_string(str);
	assert_true(sval_cast_to_int(v) == 23);
	assert_true(sval_cast_to_double(v) == (double) 23.45);
}

void soft_test_sval_arithmetic_int(void ** state)
{
	sval_t v;

	sval_t i      = sval_from_int(17);
	sval_t d      = sval_from_double(12.3);
	sval_t istr   = sval_from_string(smalloc(sizeof(char) * 2));
	sval_t dstr   = sval_from_string(smalloc(sizeof(char) * 5));
	sval_t nanstr = sval_from_string(smalloc(sizeof(char) * 6));

	strcpy(sval_to_string(istr), "73");
	strcpy(sval_to_string(dstr), "54.32");
	strcpy(sval_to_string(nanstr), "1.5NaN");

	/* dynamic integer arithmetic */
	sval_arithmetic(v, i, +, i);
	assert_true(sval_to_int(v) == 34);
	sval_arithmetic(v, i, +, d);
	assert_true(sval_to_double(v) == 29.3);
	sval_arithmetic(v, i, +, istr);
	assert_true(sval_to_int(v) == 90);
	sval_arithmetic(v, i, +, dstr);
	assert_true(sval_to_double(v) == 71.32);
	sval_arithmetic(v, i, +, sval_nan());
	assert_true(sval_is_nan(v));
	sval_arithmetic(v, i, +, nanstr);
	assert_true(sval_is_nan(v));
}

void soft_test_sval_arithmetic_double(void ** state)
{
	sval_t v;

	sval_t i      = sval_from_int(17);
	sval_t d      = sval_from_double(12.3);
	sval_t istr   = sval_from_string(smalloc(sizeof(char) * 2));
	sval_t dstr   = sval_from_string(smalloc(sizeof(char) * 5));
	sval_t nanstr = sval_from_string(smalloc(sizeof(char) * 6));

	strcpy(sval_to_string(istr), "73");
	strcpy(sval_to_string(dstr), "54.32");
	strcpy(sval_to_string(nanstr), "1.5NaN");

	/* dynamic integer arithmetic */
	sval_arithmetic(v, d, +, i);
	assert_true(sval_to_double(v) == 29.3);
	sval_arithmetic(v, d, +, d);
	assert_true(sval_to_double(v) == 24.6);
	sval_arithmetic(v, d, +, istr);
	assert_true(sval_to_double(v) == 85.3);
	sval_arithmetic(v, d, +, dstr);
	assert_true(sval_to_double(v) == 66.62);
	sval_arithmetic(v, d, +, sval_nan());
	assert_true(sval_is_nan(v));
	sval_arithmetic(v, d, +, nanstr);
	assert_true(sval_is_nan(v));
}

void soft_test_sval_arithmetic_string(void ** state)
{
	sval_t v;

	sval_t i      = sval_from_int(17);
	sval_t d      = sval_from_double(12.3);
	sval_t istr   = sval_from_string(smalloc(sizeof(char) * 2));
	sval_t dstr   = sval_from_string(smalloc(sizeof(char) * 5));
	sval_t nanstr = sval_from_string(smalloc(sizeof(char) * 6));

	strcpy(sval_to_string(istr), "73");
	strcpy(sval_to_string(dstr), "54.32");
	strcpy(sval_to_string(nanstr), "1.5NaN");

	sval_arithmetic(v, istr, +, i);
	assert_true(sval_to_int(v) == 90);
	sval_arithmetic(v, istr, +, d);
	assert_true(sval_to_double(v) == 85.3);
	sval_arithmetic(v, istr, +, istr);
	assert_true(sval_to_int(v) == 146);
	sval_arithmetic(v, istr, +, dstr);
	assert_true(sval_to_double(v) == 127.32);
	sval_arithmetic(v, istr, +, sval_nan());
	assert_true(sval_is_nan(v));
	sval_arithmetic(v, istr, +, nanstr);
	assert_true(sval_is_nan(v));

	sval_arithmetic(v, dstr, +, i);
	assert_true(sval_to_double(v) == 71.32);
	sval_arithmetic(v, dstr, +, d);
	assert_true(sval_to_double(v) == 66.62);
	sval_arithmetic(v, dstr, +, istr);
	assert_true(sval_to_double(v) == 127.32);
	sval_arithmetic(v, dstr, +, dstr);
	assert_true(sval_to_double(v) == 108.64);
	sval_arithmetic(v, dstr, +, sval_nan());
	assert_true(sval_is_nan(v));
	sval_arithmetic(v, dstr, +, nanstr);
	assert_true(sval_is_nan(v));
}

