#include "vm/vm-test.h"

void soft_vm_test_load_dw(void ** state)
{
	size_t dword_in_chars = sizeof(doubleword_t) / sizeof(char);
	size_t ds_len = 3 * dword_in_chars;
	char * datastore = (char *) smalloc(ds_len);
	sval_t i = sval_from_int(17);
	sval_t d = sval_from_double(17.17);
	char * ds = &datastore;
	memcpy(datastore, &i, sizeof(doubleword_t));
	memcpy(datastore + dword_in_chars, &d, sizeof(doubleword_t));
	memcpy(datastore + (2 * dword_in_chars), &ds, sizeof(doubleword_t));

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rax, 0),
		sinstr(load_dw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(load_dw, 0, soft_rcx, 2 * sizeof(sval_t) / sizeof(char)),
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
	assert_true((char *) vm.r[soft_rcx].dw == &datastore);
}

void soft_vm_test_loadi(void ** state)
{
	sval_t i = sval_from_int(27);

	sval_t datastore[] = {
		sval_from_pointer(&i),
	};

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rax, 0),
		sinstr(loadi, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rbx].sval) == 27);
}
