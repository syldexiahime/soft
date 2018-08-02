#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "utils/util-test.h"
#include "utils/charstream.h"

soft_charstream charstream;
char test_string[] = "Hello World!";

void soft_charstream_test_peek(void **state)
{
	soft_charstream_init(&charstream, test_string);
	char peeked = soft_charstream_peek(&charstream);

	assert_true(peeked == 'H');
	assert_true(charstream.index == 0);
}

void soft_charstream_test_consume(void **state)
{
	soft_charstream_init(&charstream, test_string);
	char consumed = soft_charstream_consume(&charstream);
	char peeked = soft_charstream_peek(&charstream);

	assert_true(consumed == 'H');
	assert_true(peeked   == 'e');
	assert_true(charstream.index == 1);
}

void soft_charstream_test_eof(void **state)
{
	bool eof;
	char eof_test_string[] = "hi";
	char consumed;
	soft_charstream_init(&charstream, eof_test_string);

	assert_false(soft_charstream_eof(&charstream));
	assert_true(charstream.index == 0);

	soft_charstream_consume(&charstream);
	assert_false(soft_charstream_eof(&charstream));
	assert_true(charstream.index == 1);

	soft_charstream_consume(&charstream);
	assert_true(soft_charstream_eof(&charstream));
	assert_true(charstream.index == 2);
}

bool expect_e(char ch) { return ch == 'e'; }
void soft_charstream_test_expect(void **state)
{
	bool expected;
	soft_charstream_init(&charstream, test_string);

	expected = soft_charstream_expect(&charstream, expect_e);
	assert_false(expected);

	soft_charstream_consume(&charstream);

	expected = soft_charstream_expect(&charstream, expect_e);
	assert_true(expected);
}

void soft_charstream_test_skip(void **state)
{
	bool peeked;
	soft_charstream_init(&charstream, test_string);

	peeked = soft_charstream_peek(&charstream);
	soft_charstream_skip(&charstream);
	assert_true(peeked != soft_charstream_peek(&charstream));
}

void soft_charstream_test_read_while(void **state)
{
	char * str;
	char expected[] = "Hello";
	soft_charstream_init(&charstream, test_string);

	str = soft_charstream_read_while(&charstream, (bool (*)(char)) isnumber);
	assert_true(strlen(str) == 0);

	str = soft_charstream_read_while(&charstream, (bool (*)(char)) isalpha);
	assert_true(strlen(str) != 0);
	assert_true(strcmp(str, expected) == 0);
	assert_false(strcmp(str, test_string) == 0);
}
