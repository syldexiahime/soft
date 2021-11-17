#include "soft-test.h"
#include "utils/util-test.h"

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(soft_test_str_replace_at),

		cmocka_unit_test(soft_test_parse_numbers),
		cmocka_unit_test(soft_test_numbers_to_str),

		cmocka_unit_test(soft_test_str_is_number),

		cmocka_unit_test(soft_test_tagged_pointers),

		cmocka_unit_test(soft_test_charstream_peek),
		cmocka_unit_test(soft_test_charstream_consume),
		cmocka_unit_test(soft_test_charstream_eof),
		cmocka_unit_test(soft_test_charstream_expect),
		cmocka_unit_test(soft_test_charstream_skip),
		cmocka_unit_test(soft_test_charstream_read_while),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
