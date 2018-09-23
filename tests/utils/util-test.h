#ifndef _SOFT_UTILS_TEST_H
#define _SOFT_UTILS_TEST_H

#include "soft-test.h"
#include "utils/helpers.h"
#include "utils/charstream.h"

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


void soft_charstream_test_peek(void **state);
void soft_charstream_test_consume(void **state);
void soft_charstream_test_eof(void **state);
void soft_charstream_test_expect(void **state);
void soft_charstream_test_skip(void **state);
void soft_charstream_test_read_while(void **state);

void soft_test_str_replace_at(void **state);

#endif // _SOFT_UTILS_TEST_H
