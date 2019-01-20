#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_store_dw(void ** state)
{
	sval_t d = sval_from_double(23.45);
	sval_t i = sval_from_int(17);

	sval_t datastore[] = {
		d,
		sval_from_pointer(&i),
	};

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rax, 0),
		sinstr(load_dw, 0, soft_rbx, 8),
		sinstr(store_dw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_is_double(i));
	assert_true(sval_to_double(i) == 23.45);
}

