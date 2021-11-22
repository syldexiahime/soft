#include "soft-test.h"
#include "vm/vm-test.h"

int main (void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(soft_vm_test_loadi_dw),
		cmocka_unit_test(soft_vm_test_loadi_qw),
		cmocka_unit_test(soft_vm_test_store_dw),
		cmocka_unit_test(soft_vm_test_store_qw),
		cmocka_unit_test(soft_vm_test_storep_dw),
		cmocka_unit_test(soft_vm_test_storep_qw),
		cmocka_unit_test(soft_vm_test_storemem_dw),
		cmocka_unit_test(soft_vm_test_storemem_qw),
		cmocka_unit_test(soft_vm_test_memset_dw),
		cmocka_unit_test(soft_vm_test_memset_qw),
		cmocka_unit_test(soft_vm_test_memsetp_dw),
		cmocka_unit_test(soft_vm_test_memsetp_qw),
		cmocka_unit_test(soft_vm_test_movi),
		cmocka_unit_test(soft_vm_test_mov),

		cmocka_unit_test(soft_vm_test_dynamic_arithmetic),
		cmocka_unit_test(soft_vm_test_dynamic_comparison),
		cmocka_unit_test(soft_vm_test_dynamic_bitwise),

		cmocka_unit_test(soft_vm_test_push_qw_and_pop_qw),

		cmocka_unit_test(soft_vm_test_jmp),
		cmocka_unit_test(soft_vm_test_jmpz),
		cmocka_unit_test(soft_vm_test_jmpnz),
		cmocka_unit_test(soft_vm_test_jmpgt),
		cmocka_unit_test(soft_vm_test_jmpgte),
		cmocka_unit_test(soft_vm_test_jmplt),
		cmocka_unit_test(soft_vm_test_jmplte),
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

