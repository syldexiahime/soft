#include "soft-test.h"
#include "vm/vm-test.h"

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(soft_test_sval_null),
		cmocka_unit_test(soft_test_sval_nan),
		cmocka_unit_test(soft_test_sval_true),
		cmocka_unit_test(soft_test_sval_false),
		cmocka_unit_test(soft_test_sval_bool),
		cmocka_unit_test(soft_test_sval_int),
		cmocka_unit_test(soft_test_sval_double),
		cmocka_unit_test(soft_test_sval_pointer),
		cmocka_unit_test(soft_test_sval_string),
		cmocka_unit_test(soft_test_sval_falsey),
		cmocka_unit_test(soft_test_sval_casts),
		cmocka_unit_test(soft_test_sval_arithmetic_int),
		cmocka_unit_test(soft_test_sval_arithmetic_double),
		cmocka_unit_test(soft_test_sval_arithmetic_string),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

