#include "vm/vm-test.h"

void soft_vm_test_dynamic_arithmetic_int(void ** state)
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
	};

	struct soft_instr instructions[] = {
		sinstr(dload, 1, 0, soft_rax, 0),
		sinstr(dload, 1, 0, soft_rbx, 1),
		sinstr(dload, 1, 0, soft_rcx, 2),
		sinstr(dload, 1, 0, soft_rdx, 3),
		sinstr(dadd, 0, soft_rax, soft_rdi, soft_rax),
		sinstr(dadd, 0, soft_rax, soft_rsi, soft_rbx),
		sinstr(dadd, 0, soft_rax, soft_rsp, soft_rcx),
		sinstr(dadd, 0, soft_rax, soft_rbp, soft_rdx),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rdi]) == 34);
	assert_true(sval_to_double(vm.r[soft_rsi]) == 29.3);
	assert_true(sval_to_int(vm.r[soft_rsp]) == 90);
	assert_true(sval_to_double(vm.r[soft_rbp]) == 71.32);
}

void soft_vm_test_dynamic_arithmetic_double(void ** state)
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
	};

	struct soft_instr instructions[] = {
		sinstr(dload, 1, 0, soft_rax, 0),
		sinstr(dload, 1, 0, soft_rbx, 1),
		sinstr(dload, 1, 0, soft_rcx, 2),
		sinstr(dload, 1, 0, soft_rdx, 3),
		sinstr(dadd, 0, soft_rbx, soft_rdi, soft_rax),
		sinstr(dadd, 0, soft_rbx, soft_rsi, soft_rbx),
		sinstr(dadd, 0, soft_rbx, soft_rsp, soft_rcx),
		sinstr(dadd, 0, soft_rbx, soft_rbp, soft_rdx),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_double(vm.r[soft_rdi]) == 29.3);
	assert_true(sval_to_double(vm.r[soft_rsi]) == 24.6);
	assert_true(sval_to_double(vm.r[soft_rsp]) == 85.3);
	assert_true(sval_to_double(vm.r[soft_rbp]) == 66.62);
}

void soft_vm_test_dynamic_arithmetic_string(void ** state)
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
	};

	struct soft_instr instructions[] = {
		sinstr(dload, 1, 0, soft_rax, 0),
		sinstr(dload, 1, 0, soft_rbx, 1),
		sinstr(dload, 1, 0, soft_rcx, 2),
		sinstr(dload, 1, 0, soft_rdx, 3),
		sinstr(dadd, 0, soft_rcx, soft_rdi, soft_rax),
		sinstr(dadd, 0, soft_rcx, soft_rsi, soft_rbx),
		sinstr(dadd, 0, soft_rcx, soft_rsp, soft_rcx),
		sinstr(dadd, 0, soft_rcx, soft_rbp, soft_rdx),
		sinstr(breakpoint, 0, 0, 0, 0),
		sinstr(dadd, 0, soft_rdx, soft_rdi, soft_rax),
		sinstr(dadd, 0, soft_rdx, soft_rsi, soft_rbx),
		sinstr(dadd, 0, soft_rdx, soft_rsp, soft_rcx),
		sinstr(dadd, 0, soft_rdx, soft_rbp, soft_rdx),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);

	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rdi]) == 90);
	assert_true(sval_to_double(vm.r[soft_rsi]) == 85.3);
	assert_true(sval_to_int(vm.r[soft_rsp]) == 146);
	assert_true(sval_to_double(vm.r[soft_rbp]) == 127.32);

	soft_vm_run_vm(&vm);

	assert_true(sval_to_double(vm.r[soft_rdi]) == 71.32);
	assert_true(sval_to_double(vm.r[soft_rsi]) == 66.62);
	assert_true(sval_to_double(vm.r[soft_rsp]) == 127.32);
	assert_true(sval_to_double(vm.r[soft_rbp]) == 108.64);
}

