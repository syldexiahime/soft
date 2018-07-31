#ifndef _SOFT_UTILS_TEST_H
#define _SOFT_UTILS_TEST_H

#include "soft-test.h"
#include "utils/charstream.h"

void soft_charstream_test_peek(void **state);
void soft_charstream_test_consume(void **state);
void soft_charstream_test_eof(void **state);
void soft_charstream_test_expect(void **state);

#endif // _SOFT_UTILS_TEST_H
