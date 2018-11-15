#include "utils/util-test.h"

void soft_test_str_replace_at(void **state)
{
	char * str = malloc(32 * sizeof(char));

	strcpy(str, "Hello World!");

	str = str_replace_at(str, "Darkness My Old Friend", 6, 5);
	assert_true(strcmp(str, "Hello Darkness My Old Friend!") == 0);

	strcpy(str, "H%1 %2ld!");

	str = str_replace_at(str, "ello", 1, 2);
	assert_true(strcmp(str, "Hello %2ld!") == 0);

	str = str_replace_at(str, "Wor", 6, 2);
	assert_true(strcmp(str, "Hello World!") == 0);
}

void soft_test_parse_numbers(void ** state)
{
	assert_true(parse_int("27") == 27);
	assert_true(parse_hex("0xF") == 15);
	assert_true(parse_oct("12") == 10);
	assert_true(parse_float("23.45") == 23.45f);
	assert_true(parse_double("23.45") == 23.45);
}

void soft_test_numbers_to_str(void ** state)
{
	char * str;

	assert_true(strcmp(int_to_str(345), "345") == 0);
	assert_true(strcmp(float_to_str(23.45f), "23.450001") == 0);
	assert_true(strcmp(double_to_str(23.45), "23.450000") == 0);
}

