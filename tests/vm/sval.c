#include "vm/vm-test.h"
#include <math.h>

union sval v;

void soft_test_sval_null(void ** state)
{
	v = sval_null();

	assert_true(sval_is_null(v));

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
}
