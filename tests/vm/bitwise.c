#include "vm/vm-test.h"

void soft_vm_test_dynamic_bitwise(void ** state)
{
	char * istr = smalloc(sizeof(char) * 2);
	char * dstr = smalloc(sizeof(char) * 5);
	strcpy(istr, "73");
	strcpy(dstr, "54.32");

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_double(12.3),
		sval_from_string(istr),
		sval_from_string(dstr),
		sval_from_int(54321),
		sval_from_int(2),
	};

	struct soft_instr instructions[] = {
		sinstr(load_dw, 1, soft_rax, 0),
		sinstr(load_dw, 1, soft_rbx, 8),
		sinstr(load_dw, 1, soft_rcx, 16),
		sinstr(load_dw, 1, soft_rdx, 24),
		sinstr(dand, soft_rax, soft_rdi, soft_rbx),
		sinstr(dor,  soft_rax, soft_rsi, soft_rcx),
		sinstr(dnot, soft_rax, soft_rsp, 0),
		sinstr(dxor, soft_rax, soft_rbp, soft_rdx),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(load_dw, 0, soft_rax, 32),
		sinstr(load_dw, 0, soft_rbx, 40),
		sinstr(dlshift, soft_rax, soft_rdi, soft_rbx),
		sinstr(drshift, soft_rax, soft_rsi, soft_rbx),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rdi].sval) == (17 & 12));
	assert_true(sval_to_int(vm.r[soft_rsi].sval) == (17 | 73));
	assert_true(sval_to_int(vm.r[soft_rsp].sval) == (~ 17));
	assert_true(sval_to_int(vm.r[soft_rbp].sval) == (17 ^ 54));

	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rdi].sval) == (54321 << 2));
	assert_true(sval_to_int(vm.r[soft_rsi].sval) == (54321 >> 2));

}

