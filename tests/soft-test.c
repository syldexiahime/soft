#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "soft-test.h"
#include "soft.h"
#include "vm/vm-test.h"
#include "utils/util-test.h"

#define SOFT_VM_TESTS 1
#define SOFT_UTILS_TESTS 1

#define REGISTER_VM_UNIT_TEST_SUITE(instr) \
	cmocka_unit_test(soft_vm_test_##instr##_int32_reg), \
	cmocka_unit_test(soft_vm_test_##instr##_int32_imm), \
	cmocka_unit_test(soft_vm_test_##instr##_float_reg), \
	cmocka_unit_test(soft_vm_test_##instr##_float_imm)

int main(void) {
    const struct CMUnitTest tests[] = {

		/**
		 * Virtual machine tests
		 * */
		#ifdef SOFT_VM_TESTS
        cmocka_unit_test(soft_vm_test_load_int32),
        cmocka_unit_test(soft_vm_test_load_float),

		REGISTER_VM_UNIT_TEST_SUITE(mov),

		REGISTER_VM_UNIT_TEST_SUITE(add),
		REGISTER_VM_UNIT_TEST_SUITE(sub),
		REGISTER_VM_UNIT_TEST_SUITE(mul),
		REGISTER_VM_UNIT_TEST_SUITE(div),

		cmocka_unit_test(soft_vm_test_and_int32_reg),
		cmocka_unit_test(soft_vm_test_or_int32_reg),
		cmocka_unit_test(soft_vm_test_xor_int32_reg),
		cmocka_unit_test(soft_vm_test_lshift_int32_reg),
		cmocka_unit_test(soft_vm_test_rshift_int32_reg),

		cmocka_unit_test(soft_vm_test_and_int32_imm),
		cmocka_unit_test(soft_vm_test_or_int32_imm),
		cmocka_unit_test(soft_vm_test_xor_int32_imm),
		cmocka_unit_test(soft_vm_test_lshift_int32_imm),
		cmocka_unit_test(soft_vm_test_rshift_int32_imm),

		REGISTER_VM_UNIT_TEST_SUITE(eq),
		REGISTER_VM_UNIT_TEST_SUITE(gt),
		REGISTER_VM_UNIT_TEST_SUITE(lt),
		REGISTER_VM_UNIT_TEST_SUITE(gteq),
		REGISTER_VM_UNIT_TEST_SUITE(lteq),

		cmocka_unit_test(soft_vm_test_jmp),
		cmocka_unit_test(soft_vm_test_jmpz),
		cmocka_unit_test(soft_vm_test_jmpnz),
		#endif

		#ifdef SOFT_UTILS_TESTS
		cmocka_unit_test(soft_charstream_test_peek),
		cmocka_unit_test(soft_charstream_test_consume),
		cmocka_unit_test(soft_charstream_test_eof),
		#endif
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
