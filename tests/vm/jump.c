#include "vm/vm-test.h"

void soft_vm_test_jmp (void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(jmp, soft_rax, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 4,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
}

void soft_vm_test_jmpz(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rbx),
		sinstr(jmpz, soft_rax, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 6,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 34);
}

void soft_vm_test_jmpnz(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rcx),
		sinstr(jmpnz, soft_rax, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 7,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 34);
}

void soft_vm_test_jmpgt(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rcx),
		sinstr(jmpgt, soft_rax, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 7,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 34);
}

void soft_vm_test_jmpgte(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rcx),
		sinstr(jmpgte, soft_rax, 0, 0),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 3 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rbx),
		sinstr(jmpgte, soft_rax, 0, 0),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 6,
		instructions + 10,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
}

void soft_vm_test_jmplt(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rcx, 0, soft_rbx),
		sinstr(jmplt, soft_rax, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 7,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
}

void soft_vm_test_jmplte(void ** state)
{
	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 2 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rbx, 1 * sizeof(sval_t) / sizeof(char)),
		sinstr(loadi_qw, 0, soft_rcx, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rcx, 0, soft_rbx),
		sinstr(jmplte, soft_rax, 0, 0),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 3 * sizeof(sval_t) / sizeof(char)),
		sinstr(dcmp, soft_rbx, 0, soft_rbx),
		sinstr(jmplte, soft_rax, 0, 0),
		sinstr(halt, 0, 0, 0),
		sinstr(loadi_qw, 0, soft_rax, 0 * sizeof(sval_t) / sizeof(char)),
		sinstr(halt, 0, 0, 0),
	};

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_int(34),
		instructions + 6,
		instructions + 10,
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(vm.r[soft_rax].sval) == 17);
}
