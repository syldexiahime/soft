#include "vm/vm-test.h"

void soft_vm_test_loadi_dw (void ** state)
{
	size_t dword_in_chars = sizeof(doubleword_t) / sizeof(char);
	size_t ds_len = 2 * dword_in_chars;
	char * datastore = (char *) smalloc(ds_len);
	doubleword_t i = TEST_DWORD;
	doubleword_t d = TEST_DWORD_2;
	char * ds = &datastore;
	memcpy(datastore, &i, sizeof(doubleword_t));
	memcpy(datastore + dword_in_chars, &d, sizeof(doubleword_t));

	struct soft_instr instructions[] = {
		sinstr(loadi_dw, 0, soft_rax, 0),
		sinstr(loadi_dw, 0, soft_rbx, 1 * sizeof(doubleword_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(vm.r[soft_rax].dw == i);
	assert_true(vm.r[soft_rbx].dw == d);
}

void soft_vm_test_loadi_qw (void ** state)
{
	size_t qword_in_chars = sizeof(quadword_t) / sizeof(char);
	size_t ds_len = 3 * qword_in_chars;
	char * datastore = (char *) smalloc(ds_len);
	sval_t i = sval_from_int(17);
	sval_t d = sval_from_double(17.17);
	char * ds = &datastore;
	memcpy(datastore, &i, sizeof(quadword_t));
	memcpy(datastore + qword_in_chars, &d, sizeof(quadword_t));
	memcpy(datastore + (2 * qword_in_chars), &ds, sizeof(quadword_t));

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
	assert_true(sval_to_double(vm.r[soft_rbx].sval) == 17.17);
	assert_true((char *) vm.r[soft_rcx].qw == &datastore);
}
