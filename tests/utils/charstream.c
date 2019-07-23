#include "utils/util-test.h"
#include "utils/charstream.h"

struct soft_charstream * charstream;
char test_string[] = "Hello World!";

void soft_test_charstream_peek(void **state)
{
	charstream = soft_charstream_init(test_string);
	char peeked = soft_charstream_peek();

	assert_true(peeked == 'H');
	assert_true(charstream->index == 0);
}

void soft_test_charstream_consume(void **state)
{
	charstream = soft_charstream_init(test_string);

	char peeked = soft_charstream_peek();

	assert_true(peeked == 'H');
	assert_true(charstream->index == 0);

	char consumed = soft_charstream_consume();
	     peeked   = soft_charstream_peek();

	assert_true(consumed == 'H');
	assert_true(peeked   == 'e');
	assert_true(charstream->index == 1);
}

void soft_test_charstream_eof(void **state)
{
	bool eof;
	char eof_test_string[] = "hi";
	char consumed;
	charstream = soft_charstream_init(eof_test_string);

	assert_false(soft_charstream_eof());
	assert_true(charstream->index == 0);

	soft_charstream_consume();
	assert_false(soft_charstream_eof());
	assert_true(charstream->index == 1);

	soft_charstream_consume();
	assert_true(soft_charstream_eof());
	assert_true(charstream->index == 2);
}

bool expect_e(char ch) { return ch == 'e'; }
void soft_test_charstream_expect(void **state)
{
	bool expected;
	charstream = soft_charstream_init(test_string);

	expected = soft_charstream_expect(expect_e);
	assert_false(expected);

	soft_charstream_consume();

	expected = soft_charstream_expect(expect_e);
	assert_true(expected);
}

void soft_test_charstream_skip(void **state)
{
	bool peeked;
	soft_charstream_init(test_string);

	peeked = soft_charstream_peek();
	soft_charstream_skip();
	assert_true(peeked != soft_charstream_peek());
}

void soft_test_charstream_read_while(void **state)
{
	char * str;
	char expected[] = "Hello";
	soft_charstream_init(test_string);

	str = soft_charstream_read_while((bool (*)(char)) isnumber);
	assert_true(strlen(str) == 0);

	str = soft_charstream_read_while((bool (*)(char)) isalpha);
	assert_true(strlen(str) != 0);
	assert_true(strcmp(str, expected) == 0);
	assert_false(strcmp(str, test_string) == 0);
}
