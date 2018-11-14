#include "vm/vm-test.h"
#include <stdlib.h>

void soft_vm_test_dmovi(void **state)
{
	struct soft_instr instructions[] = {
		sinstr(dmovi, 0, 0, soft_rax, 17),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = NULL,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax]) == 17);
}

void soft_vm_test_dmov(void **state)
{
	sval_t datastore[] = {
		sval_from_int(17),
	};

	struct soft_instr instructions[] = {
		sinstr(dload, 0, 0, soft_rax, 0),
		sinstr(dmov, 0, soft_rax, soft_rbx, soft_rax),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rbx]) == 17);
}

