#include "vm/vm-test.h"

void soft_vm_test_load_dw(void ** state)
{
	sval_t datastore[] = {
		sval_from_int(17),
	};

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rax, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
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
