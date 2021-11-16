#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_store_dw (void ** state)
{
	doubleword_t d = (doubleword_t) -20399257600.0;
	doubleword_t i = 2864345431;

	char datastore[sizeof(doubleword_t) + sizeof(quadword_t)];

	*((doubleword_t *) datastore) = d;
	*((quadword_t *) (datastore + sizeof(doubleword_t))) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_dw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, sizeof(doubleword_t)),
		sinstr(store_dw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != 2864345431);
	assert_true(i == d);
}

void soft_vm_test_dstore (void ** state)
{
	sval_t d = sval_from_double(23.45);
	sval_t i = sval_from_int(17);

	sval_t datastore[] = {
		d,
		sval_from_pointer(&i),
	};

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, sizeof(quadword_t)),
		sinstr(dstore, soft_rax, soft_rbx, 0),
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

