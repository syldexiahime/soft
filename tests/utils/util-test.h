#ifndef _SOFT_UTILS_TEST_H
#define _SOFT_UTILS_TEST_H

#include "soft-test.h"
#include "utils/helpers.h"
#include "utils/tagged-pointer.h"

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void soft_test_str_replace_at(void **state);

void soft_test_parse_numbers(void ** state);
void soft_test_numbers_to_str(void ** state);

void soft_test_str_is_number(void ** state);

void soft_test_tagged_pointers(void ** state);

#endif // _SOFT_UTILS_TEST_H
