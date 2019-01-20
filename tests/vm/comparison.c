#include "vm/vm-test.h"

void soft_vm_test_dynamic_comparison(void ** state)
{
	char * istr = smalloc(sizeof(char) * 2);
	char * dstr = smalloc(sizeof(char) * 5);
	char * nanstr = smalloc(sizeof(char));
	strcpy(istr, "17");
	strcpy(dstr, "17.00");
	strcpy(nanstr, "a");

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_double(17),
		sval_from_string(istr),
		sval_from_string(dstr),
		sval_from_string(nanstr),
	};

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rax, 0),
		sinstr(load_dw, 0, soft_rbx, 8),
		sinstr(load_dw, 0, soft_rcx, 16),
		sinstr(load_dw, 0, soft_rdx, 24),
		sinstr(dcmp, soft_rax, 0, soft_rax),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(dcmp, soft_rax, 0, soft_rbx),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(dcmp, soft_rax, 0, soft_rcx),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(dcmp, soft_rax, 0, soft_rdx),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(load_dw, 0, soft_rbx, 32),
		sinstr(dcmp, soft_rax, 0, soft_rbx),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);

	soft_vm_run_vm(&vm);
	assert_true(vm.zf == 1);
	assert_true(vm.sf == 0);

	soft_vm_run_vm(&vm);
	assert_true(vm.zf == 1);
	assert_true(vm.sf == 0);

	soft_vm_run_vm(&vm);
	assert_true(vm.zf == 1);
	assert_true(vm.sf == 0);

	soft_vm_run_vm(&vm);
	assert_true(vm.zf == 1);
	assert_true(vm.sf == 0);

	soft_vm_run_vm(&vm);
	assert_true(vm.zf == 0);
	assert_true(vm.sf == 0);

}
