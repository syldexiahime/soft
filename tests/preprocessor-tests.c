#include "soft-test.h"
#include "preprocessor/preprocessor-test.h"

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(soft_preprocessor_test_parse_macro_args),
		cmocka_unit_test(soft_preprocessor_test_build_macro),
		cmocka_unit_test(soft_preprocessor_test_define_macro),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

