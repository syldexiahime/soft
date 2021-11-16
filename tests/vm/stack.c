#include "vm/vm-test.h"
#include <stdlib.h>

void soft_vm_test_push_qw_and_pop_qw (void ** state)
{
	size_t stack_len = sizeof(char *) + sizeof(sval_t);
	char * stack = smalloc(stack_len);
	char * stack_top = stack + stack_len;
	sval_t i = sval_from_int(17);

	char * datastore = smalloc(stack_len / sizeof(char));
	memcpy(datastore, &stack_top, sizeof(char *));
	memcpy(datastore + sizeof(char *), &i, sizeof(sval_t));

	struct soft_instr instructions[] = {
		sinstr(loadi_qw, 0, soft_rsp, 0),
		sinstr(loadi_qw, 0, soft_rax, sizeof(char *)),
		sinstr(push_qw, soft_rax, 0, 0),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(pop_qw, 0, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(* (sval_t *) stack_top) == 17);
	assert_true(vm.r[soft_rsp].qw == stack_top - sizeof(quadword_t));

	soft_vm_run_vm(&vm);

	assert_true(bitwise_cast(quadword_t *, quadword_t, vm.r[soft_rsp].qw) == &stack[stack_len]);
	assert_true(sval_to_int(vm.r[soft_rbx].sval) == 17);

	sfree(stack);
	sfree(datastore);
}

