#include "soft-test.h"

#define SOFT_VM_TESTS 1
#define SOFT_UTILS_TESTS 1

int main(void) {
	const struct CMUnitTest tests[] = {

		#ifdef SOFT_UTILS_TESTS
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

		cmocka_unit_test(soft_vm_test_load_dw),
		cmocka_unit_test(soft_vm_test_loadi),
		cmocka_unit_test(soft_vm_test_store_dw),
		cmocka_unit_test(soft_vm_test_movi),
		cmocka_unit_test(soft_vm_test_mov),

		cmocka_unit_test(soft_vm_test_dynamic_arithmetic),
		cmocka_unit_test(soft_vm_test_dynamic_comparison),
		cmocka_unit_test(soft_vm_test_dynamic_bitwise),

		cmocka_unit_test(soft_vm_test_push_dw_and_pop_dw),

		cmocka_unit_test(soft_vm_test_jmp),
		cmocka_unit_test(soft_vm_test_jmpz),
		cmocka_unit_test(soft_vm_test_jmpnz),
		cmocka_unit_test(soft_vm_test_jmpgt),
		cmocka_unit_test(soft_vm_test_jmpgte),
		cmocka_unit_test(soft_vm_test_jmplt),
		cmocka_unit_test(soft_vm_test_jmplte),
		#endif

		#ifdef SOFT_ASM_TOKENIZER_TESTS
		cmocka_unit_test(soft_asm_tokenizer_test_read_section),
		cmocka_unit_test(soft_asm_tokenizer_test_read_word),
		cmocka_unit_test(soft_asm_tokenizer_test_read_number),
		cmocka_unit_test(soft_asm_tokenizer_test_read_symbol),
		cmocka_unit_test(soft_asm_tokenizer_test_skip_comment),
		#endif

		#ifdef SOFT_PREPROCESSOR_TESTS
		cmocka_unit_test(soft_preprocessor_test_parse_macro_args),
		cmocka_unit_test(soft_preprocessor_test_build_macro),
		#endif
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
