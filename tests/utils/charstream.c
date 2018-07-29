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
	boolean eof;
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