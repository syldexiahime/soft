#include "soft-test.h"

#define SOFT_VM_TESTS 1
#define SOFT_UTILS_TESTS 1

int main(void) {
	const struct CMUnitTest tests[] = {

		#ifdef SOFT_UTILS_TESTS
		cmocka_unit_test(soft_charstream_test_peek),
		cmocka_unit_test(soft_charstream_test_consume),
		cmocka_unit_test(soft_charstream_test_eof),
		cmocka_unit_test(soft_charstream_test_expect),
		cmocka_unit_test(soft_charstream_test_skip),
		cmocka_unit_test(soft_charstream_test_read_while),

		cmocka_unit_test(soft_test_str_replace_at),

		cmocka_unit_test(soft_test_parse_numbers),
		cmocka_unit_test(soft_test_numbers_to_str),

		cmocka_unit_test(soft_test_str_is_number),

		cmocka_unit_test(soft_test_tagged_pointers),
		#endif

		/**
		 * Virtual machine tests
		 * */
		#ifdef SOFT_VM_TESTS
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

		cmocka_unit_test(soft_vm_test_dloadi),
		cmocka_unit_test(soft_vm_test_dload),
		cmocka_unit_test(soft_vm_test_dstore),
		cmocka_unit_test(soft_vm_test_dmovi),
		cmocka_unit_test(soft_vm_test_dmov),

		cmocka_unit_test(soft_vm_test_dynamic_arithmetic),
		cmocka_unit_test(soft_vm_test_dynamic_comparison),
		#endif

		#ifdef SOFT_ASM_TOKENIZER_TESTS
		cmocka_unit_test(soft_asm_tokenizer_test_read_section),
		cmocka_unit_test(soft_asm_tokenizer_test_read_word),
		cmocka_unit_test(soft_asm_tokenizer_test_read_number),
		cmocka_unit_test(soft_asm_tokenizer_test_read_symbol),
		cmocka_unit_test(soft_asm_tokenizer_test_skip_comment),
		#endif
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
