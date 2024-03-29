#include "vm/vm-test.h"

void soft_vm_test_dynamic_arithmetic(void ** state)
{
	char * istr = smalloc(sizeof(char) * 2);
	char * dstr = smalloc(sizeof(char) * 5);
	char * nanstr = smalloc(sizeof(char));
	strcpy(istr, "73");
	strcpy(dstr, "54.32");
	strcpy(nanstr, "a");

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_double(12.3),
		sval_from_string(istr),
		sval_from_string(dstr),
		sval_from_string(nanstr),
	};

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, 8),
		sinstr(loadi_qw, 0, soft_rcx, 16),
		sinstr(loadi_qw, 0, soft_rdx, 24),
		sinstr(dadd, soft_rax, soft_rdi, soft_rax),
		sinstr(dadd, soft_rax, soft_rsi, soft_rbx),
		sinstr(dadd, soft_rax, soft_rsp, soft_rcx),
		sinstr(dadd, soft_rax, soft_rbp, soft_rdx),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rbx, 32),
		sinstr(dadd, soft_rax, soft_rdi, soft_rbx),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rdi].sval) == 34);
	assert_true(sval_to_double(vm.r[soft_rsi].sval) == 29.3);
	assert_true(sval_to_int(vm.r[soft_rsp].sval) == 90);
	assert_true(sval_to_double(vm.r[soft_rbp].sval) == 71.32);

	soft_vm_run_vm(&vm);

	assert_true(sval_is_nan(vm.r[soft_rdi].sval));
}

