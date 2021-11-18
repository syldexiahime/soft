#include "utils/util-test.h"
#include "lib/hashtable.h"

void soft_test_hashtable (void ** state)
{
	hashtable_t * t = ht_create();

	assert_true(ht_length(t) == 0);
	assert_false(ht_contains(t, "test"));

	char * value = "value";
	ht_set(t, "test", value);

	assert_true(ht_length(t) == 1);
	assert_true(ht_contains(t, "test"));

	assert_true(strcmp(ht_get(t, "test"), "value") == 0);

	ht_delete(t, "test");

	assert_true(ht_length(t) == 0);
	assert_false(ht_contains(t, "test"));

	ht_destroy(t);
}

void soft_test_hashtable_collision (void ** state)
{
	hashtable_t * t = ht_create();

	assert_true(ht_length(t) == 0);

	char * key1 = "8yn0iYCKYHlIj4-BwPqk";
	char * key2 = "GReLUrM4wMqfg9yzV3KQ";

	assert_true(ht_default_hashfunc(key1) == ht_default_hashfunc(key2));

	assert_false(ht_contains(t, key1));
	assert_false(ht_contains(t, key2));

	ht_set(t, key1, "value1");
	ht_set(t, key2, "value2");

	assert_true(ht_length(t) == 2);
	assert_true(ht_contains(t, key1));
	assert_true(ht_contains(t, key2));

	assert_true(strcmp(ht_get(t, key1), "value1") == 0);
	assert_true(strcmp(ht_get(t, key2), "value2") == 0);
}

void soft_test_hashtable_capacity (void ** state)
{
	hashtable_t * t = ht_create(.capacity = 3);

	assert_true(t->capacity == 3);

	ht_set(t, "1", "1");
	ht_set(t, "2", "2");

	assert_true(ht_length(t) == 2);
	assert_true(t->capacity == 6);

	ht_set(t, "3", "3");
	ht_set(t, "3", "4");

	assert_true(ht_length(t) == 4);
	assert_true(t->capacity == 12);
}
