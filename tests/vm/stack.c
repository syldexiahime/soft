#include "vm/vm-test.h"
#include <stdlib.h>

void soft_vm_test_push_dw_and_pop_dw(void ** state)
{
	size_t stack_len = sizeof(sval_t) * 2;
	char * stack = smalloc(stack_len);
	sval_t * ptr;
	ptr = stack + stack_len;
	sval_t i = sval_from_int(17);

	char * datastore = smalloc(sizeof(sval_t *) + sizeof(sval_t));
	memcpy(&datastore[0], &ptr, sizeof(sval_t *));
	memcpy(&datastore[sizeof(sval_t *)], &i, sizeof(sval_t));

	struct soft_instr instructions[] = {
		sinstr(load_dw, 0, soft_rsp, 0),
		sinstr(load_dw, 0, soft_rax, sizeof(sval_t *)),
		sinstr(push_dw, soft_rax, 0, 0),
		sinstr(breakpoint, 0, 0, 0),
		sinstr(pop_dw, 0, soft_rbx, 0),
		sinstr(halt, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(bitwise_cast(doubleword_t *, doubleword_t, vm.r[soft_rsp].dw) == &stack[stack_len - sizeof(sval_t)]);
	assert_true(sval_to_int(* (sval_t *) &stack[stack_len]) == 17);

	soft_vm_run_vm(&vm);

	assert_true(bitwise_cast(doubleword_t *, doubleword_t, vm.r[soft_rsp].dw) == &stack[stack_len]);
	assert_true(sval_to_int(vm.r[soft_rbx].sval) == 17);

	sfree(stack);
	sfree(datastore);
}

