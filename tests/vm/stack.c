#include "vm/vm-test.h"
#include <stdlib.h>

void soft_vm_test_push_dw_and_pop_dw(void ** state)
{
	size_t stack_len = sizeof(char *) + sizeof(sval_t);
	char * stack = smalloc(stack_len);
	char * stack_top = stack + stack_len;
	sval_t i = sval_from_int(17);

	char * datastore = smalloc(stack_len / sizeof(char));
	memcpy(datastore, &stack_top, sizeof(char *));
	memcpy(datastore + sizeof(char *), &i, sizeof(sval_t));

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rsp, 0),
		sinstr(load_dw, 0, soft_rax, sizeof(char *)),
		sinstr(push_dw, soft_rax, 0, 0),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(pop_dw, 0, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_to_int(* (sval_t *) stack_top) == 17);
	assert_true(vm.r[soft_rsp].dw == stack_top - sizeof(doubleword_t));

	soft_vm_run_vm(&vm);

	assert_true(bitwise_cast(doubleword_t *, doubleword_t, vm.r[soft_rsp].dw) == &stack[stack_len]);
	assert_true(sval_to_int(vm.r[soft_rbx].sval) == 17);

	sfree(stack);
	sfree(datastore);
}

