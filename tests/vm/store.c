#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_store_dw (void ** state)
{
	doubleword_t d = TEST_DWORD;
	doubleword_t i = TEST_DWORD_2;

	char * datastore = alloca(sizeof(doubleword_t) + sizeof(doubleword_t *));

	*((doubleword_t *) datastore) = d;
	*((doubleword_t **) (datastore + sizeof(doubleword_t))) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_dw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, sizeof(doubleword_t)),
		sinstr(store_dw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_DWORD_2);
	assert_true(i == d);
}

void soft_vm_test_store_qw (void ** state)
{
	quadword_t d = TEST_QWORD;
	quadword_t i = TEST_QWORD_2;

	char * datastore = alloca(sizeof(quadword_t) + sizeof(doubleword_t *));

	*((quadword_t *) datastore) = d;
	*((quadword_t **) (datastore + sizeof(quadword_t))) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_ptr, 0, soft_rbx, sizeof(quadword_t)),
		sinstr(store_qw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_QWORD_2);
	assert_true(i == d);
}

void soft_vm_test_storep_dw (void ** state)
{
	doubleword_t d = TEST_DWORD;
	doubleword_t i = TEST_DWORD_2;

	char * datastore = alloca(sizeof(doubleword_t *) + sizeof(doubleword_t **));

	*((doubleword_t **) datastore) = &d;
	*((doubleword_t **) (datastore + sizeof(doubleword_t *))) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, sizeof(doubleword_t *)),
		sinstr(storep_dw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_DWORD_2);
	assert_true(i == d);
}

void soft_vm_test_storep_qw (void ** state)
{
	quadword_t d = TEST_QWORD;
	quadword_t i = TEST_DWORD;

	char * datastore = alloca(sizeof(quadword_t *) + sizeof(quadword_t));

	*((quadword_t **) datastore) = &d;
	*((quadword_t **) (datastore + sizeof(quadword_t *))) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rax, 0),
		sinstr(loadi_qw, 0, soft_rbx, sizeof(quadword_t *)),
		sinstr(storep_qw, soft_rax, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_DWORD);
	assert_true(i == d);
}

void soft_vm_test_storemem_dw (void ** state)
{
	doubleword_t d = TEST_DWORD;
	doubleword_t i = TEST_DWORD_2;

	size_t dssize = sizeof(doubleword_t) + sizeof(doubleword_t *);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(doubleword_t);
	*((doubleword_t *) datastore) = d;
	*((doubleword_t **) (datastore + offset)) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_ptr, 0, soft_rbx, offset),
		sinstr(storemem_dw, 0, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_DWORD_2);
	assert_true(i == d);
}

void soft_vm_test_storemem_qw (void ** state)
{
	quadword_t d = TEST_QWORD;
	quadword_t i = TEST_QWORD_2;

	size_t dssize = sizeof(quadword_t) + sizeof(quadword_t *);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(quadword_t);
	*((quadword_t *) datastore) = d;
	*((quadword_t **) (datastore + offset)) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_ptr, 0, soft_rbx, offset),
		sinstr(storemem_qw, 0, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(i != TEST_QWORD_2);
	assert_true(i == d);
}

void soft_vm_test_memset_dw (void ** state)
{
	doubleword_t d = TEST_DWORD;
	doubleword_t i = TEST_DWORD_2;

	size_t dssize = sizeof(doubleword_t) + sizeof(doubleword_t);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(doubleword_t);
	*((doubleword_t *) datastore) = d;
	*((doubleword_t *) (datastore + offset)) = i;

	struct soft_instr instructions[] = {
		sinstr(loadi_dw, 0, soft_rbx, 0),
		sinstr(memset_dw, soft_rbx, 0, offset),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(*(doubleword_t *) (datastore + offset) != i);
	assert_true(*(doubleword_t *) (datastore + offset) == d);
}

void soft_vm_test_memset_qw (void ** state)
{
	quadword_t d = TEST_QWORD;
	quadword_t i = TEST_QWORD_2;

	size_t dssize = sizeof(quadword_t) + sizeof(quadword_t);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(quadword_t);
	*((quadword_t *) datastore) = d;
	*((quadword_t *) (datastore + offset)) = i;

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rbx, 0),
		sinstr(memset_qw, soft_rbx, 0, offset),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(*(quadword_t *) (datastore + offset) != i);
	assert_true(*(quadword_t *) (datastore + offset) == d);
}

void soft_vm_test_memsetp_dw (void ** state)
{
	doubleword_t d = TEST_DWORD;
	doubleword_t i = TEST_DWORD_2;

	size_t dssize = sizeof(doubleword_t) + sizeof(doubleword_t);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(doubleword_t);
	*((doubleword_t *) datastore) = d;
	*((doubleword_t **) (datastore + offset)) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_ptr, 0, soft_rbx, offset),
		sinstr(memsetp_dw, soft_rbx, 0, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(*((doubleword_t *) datastore) != TEST_DWORD);
	assert_true(*((doubleword_t *) datastore) == i);
}

void soft_vm_test_memsetp_qw (void ** state)
{
	quadword_t d = TEST_QWORD;
	quadword_t i = TEST_QWORD_2;

	size_t dssize = sizeof(quadword_t) + sizeof(quadword_t);
	char * datastore = alloca(dssize);

	unsigned int offset = sizeof(quadword_t);
	*((quadword_t *) datastore) = d;
	*((quadword_t **) (datastore + offset)) = &i;

	struct soft_instr instructions[] = {
		sinstr(loadi_ptr, 0, soft_rbx, offset),
		sinstr(memsetp_qw, soft_rbx, 0, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(*((quadword_t *) datastore) != TEST_QWORD);
	assert_true(*((quadword_t *) datastore) == i);
}
