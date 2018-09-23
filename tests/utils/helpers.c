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
